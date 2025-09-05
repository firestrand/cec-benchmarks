#!/usr/bin/env python3
"""
CEC Benchmark Validation Framework

A generic validation framework for CEC (Congress on Evolutionary Computation) 
benchmark functions across different years. Uses strategy pattern to handle
year-specific implementations while maintaining a consistent validation interface.

Supports:
- CEC2005: 25 benchmark functions with C implementation
- CEC2006: Constrained optimization problems (future)
- CEC2007-2009: Various problem sets (future)

Usage:
    python validate_cec.py --year 2005                    # Validate all CEC2005 functions
    python validate_cec.py --year 2005 --func 1 4 17      # Validate specific functions
    python validate_cec.py --year 2005 --dim 10 30        # Validate specific dimensions
    python validate_cec.py --year 2005 --type optimal     # Validate specific test types
"""

import json
import os
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, List, Optional, Tuple

import argparse
import numpy as np

# Import executors from the new module
from executors import TestType, FunctionExecutor, ExecutorFactory


# ============================================================================
# Common Data Structures
# ============================================================================


@dataclass
class ToleranceConfig:
    """Configuration for numerical tolerance thresholds."""
    # Deterministic function tolerances
    strict_atol: float = 1e-6
    strict_rtol: float = 1e-9
    
    # Magnitude-based tolerances for deterministic functions
    large_threshold: float = 1e9
    large_atol: float = 1e-3
    large_rtol: float = 1e-8
    
    medium_threshold: float = 1e6
    medium_atol: float = 1e5
    medium_rtol: float = 1e-4
    
    small_threshold: float = 1e4
    small_atol: float = 1.0
    small_rtol: float = 1e-5
    
    # Noisy function tolerances
    noise_rtol: float = 0.5
    noise_atol: float = 1e6
    noise_magnitude_min: float = 0.1
    noise_magnitude_max: float = 10.0


@dataclass
class TestResult:
    """Result of a single test case."""
    expected: float
    actual: float
    passed: bool
    error: float
    
    @property
    def status_symbol(self) -> str:
        """Return status symbol for display."""
        return "✓" if self.passed else "✗"


@dataclass
class CECConfig:
    """Configuration for a specific CEC year."""
    year: int
    implementation_dir: str
    validation_dir: str
    metadata_path: str
    num_functions: int
    supported_dimensions: List[int]
    default_test_types: List[str]


# The executor classes have been moved to the executors module


# ============================================================================
# Generic Components
# ============================================================================

class ToleranceChecker:
    """Handles tolerance checking for validation."""
    
    def __init__(self, config: ToleranceConfig = None):
        self.config = config or ToleranceConfig()
    
    def check(self, expected: float, actual: float, is_noisy: bool, 
              test_type: TestType) -> Tuple[bool, float]:
        """Check if actual value is within tolerance of expected value."""
        # Special handling for NaN values
        if np.isnan(expected) and np.isnan(actual):
            return True, 0.0  # Both NaN - considered a match
        elif np.isnan(expected) or np.isnan(actual):
            return False, float('inf')  # Only one is NaN - not a match
        
        error = abs(actual - expected)
        
        if is_noisy and test_type != TestType.OPTIMAL:
            passed = self._check_noisy(expected, actual)
        else:
            passed = self._check_deterministic(expected, actual)
        
        return passed, error
    
    def _check_noisy(self, expected: float, actual: float) -> bool:
        """Check tolerance for noisy functions."""
        if abs(expected) > 1e3:
            relative_error = abs((actual - expected) / expected) if expected != 0 else float('inf')
            passed = relative_error <= self.config.noise_rtol
        else:
            passed = abs(actual - expected) <= self.config.noise_atol
        
        # Verify magnitude is reasonable
        if expected != 0 and actual != 0:
            magnitude_ratio = abs(actual / expected)
            passed = passed and (self.config.noise_magnitude_min <= magnitude_ratio <= 
                                self.config.noise_magnitude_max)
        
        return passed
    
    def _check_deterministic(self, expected: float, actual: float) -> bool:
        """Check tolerance for deterministic functions based on magnitude."""
        abs_expected = abs(expected)
        
        if abs_expected > self.config.large_threshold:
            atol, rtol = self.config.large_atol, self.config.large_rtol
        elif abs_expected > self.config.medium_threshold:
            atol, rtol = self.config.medium_atol, self.config.medium_rtol
        elif abs_expected > self.config.small_threshold:
            atol, rtol = self.config.small_atol, self.config.small_rtol
        else:
            atol, rtol = self.config.strict_atol, self.config.strict_rtol
        
        return np.isclose(actual, expected, atol=atol, rtol=rtol)


class ValidationReporter:
    """Handles reporting of validation results."""
    
    @staticmethod
    def print_header(year: int):
        """Print validation header."""
        print("=" * 70)
        print(f"CEC{year} Benchmark Validation")
        print("=" * 70)
    
    @staticmethod
    def print_function_header(func_id: int, name: str, is_noisy: bool):
        """Print function validation header."""
        print(f"\nValidating F{func_id}: {name}")
        if is_noisy:
            print("  [NOISY FUNCTION - Using relaxed tolerance for non-optimal tests]")
            print(f"  Note: F{func_id} includes random noise in its calculation")
    
    @staticmethod
    def print_test_result(dimension: int, test_type: str, result: TestResult):
        """Print individual test result."""
        print(f"  Dim {dimension:2d}, {test_type:8s}: {result.status_symbol} ", end="")
        if result.passed:
            if result.error == 0.0 and np.isnan(result.expected):
                print("(both NaN)")
            else:
                print(f"(error: {result.error:.2e})")
        else:
            if np.isnan(result.expected) or np.isnan(result.actual):
                print(f"Expected: {result.expected}, Got: {result.actual}")
            else:
                print(f"Expected: {result.expected:.6f}, Got: {result.actual:.6f}")
    
    @staticmethod
    def print_summary(year: int, total: int, passed: int, failed: int, 
                      noisy_functions: List[str], failed_details: Dict):
        """Print validation summary."""
        print("\n" + "=" * 70)
        print(f"CEC{year} VALIDATION SUMMARY")
        print("=" * 70)
        print(f"Total Functions: {total}")
        print(f"Passed: {passed}")
        print(f"Failed: {failed}")
        
        if noisy_functions:
            print(f"Noisy Functions: {', '.join(noisy_functions)}")
        
        if failed > 0 and failed_details:
            print("\nFailed Functions:")
            for func_key, details in failed_details.items():
                print(f"  - {func_key}: {details['name']}")
                if 'failed_tests' in details:
                    for dim, tests in details['failed_tests'].items():
                        print(f"    Dim {dim}: Failed tests: {', '.join(tests)}")


# ============================================================================
# Main Validator
# ============================================================================

class CECValidator:
    """Generic validator for CEC benchmark functions."""
    
    def __init__(self, config: CECConfig):
        self.config = config
        self.executor = ExecutorFactory.create_executor(config.year, config.implementation_dir)
        self.tolerance_checker = ToleranceChecker()
        self.reporter = ValidationReporter()
        
        self._load_metadata()
    
    def _load_metadata(self):
        """Load function metadata."""
        if not Path(self.config.metadata_path).exists():
            raise FileNotFoundError(
                f"CEC{self.config.year} metadata not found at {self.config.metadata_path}.\n"
                f"This year's implementation may not be available yet."
            )
        with open(self.config.metadata_path, 'r') as f:
            self.metadata = json.load(f)
    
    def _load_validation_data(self, func_id: int) -> Dict:
        """Load validation data for a specific function."""
        func_key = f"f{func_id:02d}"
        validation_file = Path(self.config.validation_dir) / f"{func_key}.json"
        
        if not validation_file.exists():
            raise FileNotFoundError(f"Validation data not found: {validation_file}")
        
        with open(validation_file, 'r') as f:
            return json.load(f)
    
    def validate_function(self, func_id: int, dimensions: Optional[List[int]] = None,
                         test_types: Optional[List[str]] = None) -> Dict:
        """Validate a single function."""
        func_key = f"f{func_id:02d}"
        func_info = self.metadata["functions"].get(func_key)
        
        if not func_info:
            raise ValueError(f"Function F{func_id} not found in metadata")
        
        is_noisy = func_info.get("noisy", False)
        
        validation_data = self._load_validation_data(func_id)
        
        # Determine what to test
        dims_to_test = dimensions or func_info["dimensions"]
        types_to_test = test_types or self.config.default_test_types
        
        # Print header
        self.reporter.print_function_header(func_id, func_info["name"], is_noisy)
        
        # Track results
        all_passed = True
        failed_details = {}
        
        # Test each dimension and type
        for dim in dims_to_test:
            if dim not in func_info["dimensions"]:
                continue
                
            dim_data = validation_data["dimensions"].get(str(dim), {})
            
            for test_type_str in types_to_test:
                if "results" not in dim_data or test_type_str not in dim_data["results"]:
                    continue
                
                test_type = TestType(test_type_str)
                test_data = dim_data["results"][test_type_str]
                
                try:
                    # Execute function
                    actual = self.executor.run(
                        func_id, dim, test_data["input_vector"]
                    )
                    
                    # Check tolerance
                    passed, error = self.tolerance_checker.check(
                        test_data["objective_value"], 
                        actual, 
                        is_noisy,
                        test_type
                    )
                    
                    # Create result
                    result = TestResult(
                        expected=test_data["objective_value"],
                        actual=actual,
                        passed=passed,
                        error=error
                    )
                    
                    # Track failures
                    if not passed:
                        all_passed = False
                        if dim not in failed_details:
                            failed_details[dim] = []
                        failed_details[dim].append(test_type_str)
                    
                    # Report result
                    self.reporter.print_test_result(dim, test_type_str, result)
                    
                except Exception as e:
                    print(f"  Dim {dim:2d}, {test_type_str:8s}: ✗ Error: {e}")
                    all_passed = False
        
        return {
            "function": func_key,
            "name": func_info["name"],
            "passed": all_passed,
            "noisy": is_noisy,
            "failed_tests": failed_details
        }
    
    def validate_all(self) -> Dict:
        """Validate all functions for the CEC year."""
        self.reporter.print_header(self.config.year)
        
        # Build implementation
        print(f"\nBuilding CEC{self.config.year} implementation...")
        if not self.executor.build():
            print("Build failed!")
            return {
                "summary": {
                    "year": self.config.year,
                    "total": self.config.num_functions,
                    "passed": 0,
                    "failed": self.config.num_functions
                }
            }
        print("Build successful!")
        
        # Validate each function
        results = {
            "summary": {
                "year": self.config.year,
                "total": self.config.num_functions,
                "passed": 0,
                "failed": 0,
                "noisy_functions": []
            },
            "functions": {}
        }
        
        failed_details = {}
        
        for func_id in range(1, self.config.num_functions + 1):
            try:
                result = self.validate_function(func_id)
                func_key = result["function"]
                
                if result["passed"]:
                    results["summary"]["passed"] += 1
                else:
                    results["summary"]["failed"] += 1
                    failed_details[func_key] = {
                        "name": result["name"],
                        "failed_tests": result.get("failed_tests", {})
                    }
                
                if result["noisy"]:
                    results["summary"]["noisy_functions"].append(func_key)
                
                results["functions"][func_key] = result
                
            except Exception as e:
                print(f"\nError validating F{func_id}: {e}")
                results["summary"]["failed"] += 1
        
        # Print summary
        self.reporter.print_summary(
            self.config.year,
            results["summary"]["total"],
            results["summary"]["passed"],
            results["summary"]["failed"],
            results["summary"]["noisy_functions"],
            failed_details
        )
        
        # Cleanup
        self.executor.cleanup()
        
        return results
    
    def validate_specific(self, func_ids: Optional[List[int]] = None,
                         dimensions: Optional[List[int]] = None,
                         test_types: Optional[List[str]] = None) -> Dict:
        """Validate specific functions, dimensions, or test types."""
        func_ids = func_ids or list(range(1, self.config.num_functions + 1))
        results = {}
        
        for func_id in func_ids:
            try:
                result = self.validate_function(func_id, dimensions, test_types)
                results[result["function"]] = result
            except Exception as e:
                print(f"Error validating F{func_id}: {e}")
                results[f"f{func_id:02d}"] = {"passed": False, "error": str(e)}
        
        # Cleanup
        self.executor.cleanup()
        
        return results


# ============================================================================
# Configuration Registry
# ============================================================================

def get_cec_config(year: int, base_dir: str = ".") -> CECConfig:
    """Get configuration for a specific CEC year."""
    configs = {
        2005: CECConfig(
            year=2005,
            implementation_dir=f"{base_dir}/CEC2005-C",
            validation_dir=f"{base_dir}/validation_data/CEC2005",
            metadata_path=f"{base_dir}/CEC2005-C/input_data/meta_2005.json",
            num_functions=25,
            supported_dimensions=[2, 10, 30, 50],
            default_test_types=["min", "max", "optimal", "random"]
        ),
        2006: CECConfig(
            year=2006,
            implementation_dir=f"{base_dir}/CEC2006-C",
            validation_dir=f"{base_dir}/validation_data/CEC2006",
            metadata_path=f"{base_dir}/CEC2006-C/input_data/meta_2006.json",
            num_functions=24,  # CEC2006 has 24 test problems
            supported_dimensions=list(range(2, 25)),  # Variable dimensions
            default_test_types=["min", "max", "optimal", "random"]
        ),
        # Add more years as needed
    }
    
    if year not in configs:
        raise ValueError(f"CEC{year} configuration not available. Supported years: {list(configs.keys())}")
    
    return configs[year]


# ============================================================================
# Main Entry Point
# ============================================================================

def main():
    """Main entry point for the validation script."""
    parser = argparse.ArgumentParser(
        description="Generic CEC Benchmark Validation Framework",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__
    )
    
    parser.add_argument(
        "--year",
        type=int,
        required=True,
        choices=[2005, 2006, 2007, 2008, 2009],
        help="CEC competition year"
    )
    parser.add_argument(
        "--func", 
        type=int, 
        nargs='+',
        metavar="ID",
        help="Function IDs to validate"
    )
    parser.add_argument(
        "--dim", 
        type=int, 
        nargs='+',
        help="Dimensions to test"
    )
    parser.add_argument(
        "--type", 
        nargs='+',
        help="Test types to run"
    )
    parser.add_argument(
        "--base-dir",
        default=".",
        help="Base directory for CEC implementations (default: current directory)"
    )
    
    args = parser.parse_args()
    
    try:
        # Get configuration for the specified year
        config = get_cec_config(args.year, args.base_dir)
        
        # Validate dimension choices if specified
        if args.dim:
            invalid_dims = [d for d in args.dim if d not in config.supported_dimensions]
            if invalid_dims:
                print(f"Warning: Unsupported dimensions for CEC{args.year}: {invalid_dims}")
                print(f"Supported dimensions: {config.supported_dimensions}")
                args.dim = [d for d in args.dim if d in config.supported_dimensions]
        
        # Create validator
        validator = CECValidator(config)
        
        # Run validation
        if args.func or args.dim or args.type:
            results = validator.validate_specific(args.func, args.dim, args.type)
            all_passed = all(r.get("passed", False) for r in results.values())
        else:
            results = validator.validate_all()
            all_passed = results["summary"]["failed"] == 0
        
        sys.exit(0 if all_passed else 1)
        
    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()