#!/usr/bin/env python3
"""
CEC Benchmark Validation Data Generator

A generic validation data generation framework for CEC (Congress on Evolutionary Computation) 
benchmark functions across different years. Uses strategy pattern and reuses components from
the validation framework to ensure consistency.

Generates validation datasets with test vectors including:
- Min/Max boundaries 
- Optimal solutions (when known)
- Random test points
- Specific test cases for edge conditions

Usage:
    python generate_validation_data.py --year 2005 --regenerate    # Regenerate all CEC2005 data
    python generate_validation_data.py --year 2006                # Generate all CEC2006 data  
    python generate_validation_data.py --year 2005 --func 1 4 17  # Generate specific functions
    python generate_validation_data.py --year 2005 --dim 10 30    # Generate specific dimensions
    
Safety features:
- Backup existing data before regeneration
- Validate generated data by running test cases
- Comparison with existing data to detect changes
"""

import json
import os
import shutil
import sys
import tempfile
from abc import ABC, abstractmethod
from datetime import datetime
from pathlib import Path
from typing import Dict, List, Optional, Tuple, Any
from dataclasses import dataclass
import argparse
import numpy as np
import random

# Import from executors module and validation script
sys.path.append(os.path.dirname(__file__))
from executors import TestType, FunctionExecutor, ExecutorFactory
from validate_cec import CECConfig, get_cec_config


# ============================================================================
# Data Generation Configuration
# ============================================================================

@dataclass
class GenerationConfig:
    """Configuration for validation data generation."""
    # Test vector configurations
    num_random_tests: int = 3
    random_seed: int = 42
    
    # Boundary test configurations  
    boundary_offset_ratio: float = 0.01  # Slight offset from exact boundaries
    
    # Output configuration
    backup_existing: bool = True
    validate_generated: bool = True
    compare_with_existing: bool = True
    
    # Precision for numerical values
    precision: int = 6


@dataclass 
class TestCase:
    """Represents a single test case for validation data."""
    test_type: str
    input_vector: List[float] 
    expected_output: float
    description: Optional[str] = None


# ============================================================================  
# Abstract Data Generator Base
# ============================================================================

class ValidationDataGenerator(ABC):
    """Abstract base class for CEC validation data generators."""
    
    def __init__(self, config: CECConfig, gen_config: GenerationConfig):
        self.config = config
        self.gen_config = gen_config
        self.executor = ExecutorFactory.create_executor(config.year, config.implementation_dir)
        
    @abstractmethod
    def get_function_metadata(self, func_id: int) -> Dict[str, Any]:
        """Get metadata for a specific function."""
        pass
        
    @abstractmethod 
    def generate_test_vectors(self, func_id: int, dimension: int, metadata: Dict) -> List[TestCase]:
        """Generate test vectors for a function and dimension."""
        pass
        
    def generate_validation_data(self, func_ids: Optional[List[int]] = None, 
                               dimensions: Optional[List[int]] = None) -> Dict[str, Any]:
        """Generate validation data for specified functions and dimensions."""
        print(f"Generating validation data for CEC{self.config.year}")
        
        # Build implementation
        print("Building implementation...")
        if not self.executor.build():
            raise RuntimeError("Failed to build implementation")
        print("Build successful!")
        
        # Set random seed for reproducibility
        random.seed(self.gen_config.random_seed)
        np.random.seed(self.gen_config.random_seed)
        
        results = {}
        func_ids = func_ids or list(range(1, self.config.num_functions + 1))
        
        for func_id in func_ids:
            print(f"\nProcessing F{func_id:02d}...")
            try:
                func_key = f"f{func_id:02d}"
                metadata = self.get_function_metadata(func_id)
                print(f"  Loaded metadata: {metadata.get('name', 'Unknown')}")
                
                # Determine dimensions to test
                dims_to_test = dimensions or metadata.get("dimensions", self.config.supported_dimensions)
                print(f"  Testing dimensions: {dims_to_test}")
                
                func_data = {
                    "function_id": func_id,
                    "function_name": metadata.get("name", f"Function {func_id}"),
                    "date_generated": datetime.now().isoformat(),
                    "dimensions": {}
                }
                
                for dim in dims_to_test:
                    if dim not in self.config.supported_dimensions:
                        print(f"  Skipping unsupported dimension {dim}")
                        continue
                        
                    print(f"  Generating test cases for dimension {dim}...")
                    test_cases = self.generate_test_vectors(func_id, dim, metadata)
                    
                    # Execute test cases and collect results
                    dim_results = {"results": {}}
                    
                    for test_case in test_cases:
                        try:
                            actual_output = self.executor.run(func_id, dim, test_case.input_vector)
                            
                            dim_results["results"][test_case.test_type] = {
                                "input_vector": test_case.input_vector,
                                "objective_value": round(actual_output, self.gen_config.precision)
                            }
                            
                            print(f"    {test_case.test_type}: {actual_output:.6f}")
                            
                        except Exception as e:
                            print(f"    Error executing {test_case.test_type}: {e}")
                            continue
                    
                    func_data["dimensions"][str(dim)] = dim_results
                
                results[func_key] = func_data
                
            except Exception as e:
                import traceback
                print(f"Error processing F{func_id}: {e}")
                print(f"Traceback: {traceback.format_exc()}")
                continue
        
        # Cleanup
        self.executor.cleanup()
        
        return results


# ============================================================================
# CEC2005 Data Generator  
# ============================================================================

class CEC2005DataGenerator(ValidationDataGenerator):
    """Validation data generator for CEC2005."""
    
    def __init__(self, config: CECConfig, gen_config: GenerationConfig):
        super().__init__(config, gen_config)
        self.metadata_path = Path(config.metadata_path)
        
    def get_function_metadata(self, func_id: int) -> Dict[str, Any]:
        """Get CEC2005 function metadata."""
        with open(self.metadata_path, 'r') as f:
            metadata = json.load(f)
        
        func_key = f"f{func_id:02d}"
        if func_key not in metadata["functions"]:
            raise ValueError(f"Function {func_key} not found in metadata")
            
        func_info = metadata["functions"][func_key]
        
        # Add the function ID to the metadata for consistency
        func_info["id"] = func_id
        func_info["name"] = func_info.get("name", f"Function {func_id}")
        
        return func_info
        
    def generate_test_vectors(self, func_id: int, dimension: int, metadata: Dict) -> List[TestCase]:
        """Generate test vectors for CEC2005 function."""
        test_cases = []
        
        # CEC2005 functions have standard search range [-100, 100]
        search_range = [-100, 100]
        
        # Generate boundary test cases
        min_vec = [search_range[0]] * dimension
        max_vec = [search_range[1]] * dimension
        
        test_cases.extend([
            TestCase("min", min_vec, 0.0, "Minimum boundary test"),
            TestCase("max", max_vec, 0.0, "Maximum boundary test")
        ])
        
        # Generate optimal test case (shift vector)
        optimal_vec = self._get_optimal_vector(func_id, dimension)
        if optimal_vec:
            test_cases.append(
                TestCase("optimal", optimal_vec, -450.0, "Global optimum test")
            )
        
        # Generate random test cases
        for i in range(self.gen_config.num_random_tests):
            random_vec = [
                random.uniform(search_range[0], search_range[1]) 
                for _ in range(dimension)
            ]
            test_name = "random" if i == 0 else f"random{i+1}"
            test_cases.append(
                TestCase(test_name, random_vec, 0.0, f"Random test case {i+1}")
            )
        
        return test_cases
    
    def _get_optimal_vector(self, func_id: int, dimension: int) -> Optional[List[float]]:
        """Get optimal vector (shift vector) for CEC2005 function."""
        try:
            # Read shift vector from input data - try dimension-specific first, then D50
            shift_files = [
                f"shift_D{dimension}.txt",
                "shift_D50.txt"
            ]
            
            for shift_filename in shift_files:
                shift_file = Path(self.config.implementation_dir) / "input_data" / f"f{func_id:02d}" / shift_filename
                
                if shift_file.exists():
                    with open(shift_file, 'r') as f:
                        content = f.read().strip()
                        
                    # Parse space-separated values on one line or newline-separated values
                    if ' ' in content:
                        shift_data = [float(x) for x in content.split()]
                    else:
                        shift_data = [float(line.strip()) for line in content.split('\n') if line.strip()]
                        
                    if len(shift_data) >= dimension:
                        return shift_data[:dimension]
                        
        except Exception as e:
            print(f"    Warning: Could not read shift vector for F{func_id} D{dimension}: {e}")
            
        return None


# ============================================================================
# CEC2006 Data Generator
# ============================================================================

class CEC2006DataGenerator(ValidationDataGenerator):
    """Validation data generator for CEC2006 constrained optimization problems."""
    
    def __init__(self, config: CECConfig, gen_config: GenerationConfig):
        super().__init__(config, gen_config)
        # Use the standard executor from validate_cec
        self.executor = ExecutorFactory.create_executor(config.year, config.implementation_dir)
        
    def get_function_metadata(self, func_id: int) -> Dict[str, Any]:
        """Get CEC2006 function metadata."""
        with open(self.metadata_path, 'r') as f:
            metadata = json.load(f)
            
        func_key = f"g{func_id:02d}"
        if func_key not in metadata["functions"]:
            raise ValueError(f"Function g{func_id:02d} not found in CEC2006 metadata")
            
        return metadata["functions"][func_key]
    
    def generate_test_vectors(self, func_id: int, dimension: int, metadata: Dict) -> List[TestCase]:
        """Generate test vectors for CEC2006 constrained function.""" 
        test_cases = []
        
        # For CEC2006, each function has its own dimension and search ranges
        actual_dimension = metadata["properties"]["variables"]
        search_ranges = metadata["search_ranges"]
        
        # Generate boundary test cases - use search ranges for each variable
        min_vec = []
        max_vec = []
        
        if "xi" in search_ranges:
            # Uniform bounds for all variables
            bounds = search_ranges["xi"] 
            min_vec = [bounds[0]] * actual_dimension
            max_vec = [bounds[1]] * actual_dimension
        else:
            # Individual bounds for each variable
            for i in range(actual_dimension):
                var_key = f"x{i+1}"
                if var_key in search_ranges:
                    bounds = search_ranges[var_key]
                    min_vec.append(bounds[0])
                    max_vec.append(bounds[1])
                else:
                    # Default bounds if not specified
                    min_vec.append(0.0)
                    max_vec.append(10.0)
        
        test_cases.extend([
            TestCase("min", min_vec, 0.0, "Minimum boundary test"),
            TestCase("max", max_vec, 0.0, "Maximum boundary test")
        ])
        
        # Generate random test cases within bounds
        for i in range(self.gen_config.num_random_tests):
            random_vec = []
            if "xi" in search_ranges:
                bounds = search_ranges["xi"]
                random_vec = [random.uniform(bounds[0], bounds[1]) for _ in range(actual_dimension)]
            else:
                for j in range(actual_dimension):
                    var_key = f"x{j+1}"
                    if var_key in search_ranges:
                        bounds = search_ranges[var_key]
                        random_vec.append(random.uniform(bounds[0], bounds[1]))
                    else:
                        random_vec.append(random.uniform(0.0, 10.0))
            
            test_cases.append(
                TestCase("random", random_vec, 0.0, f"Random test case {i+1}")
            )
        
        # TODO: Add known optimal solutions if available
        
        return test_cases



# ============================================================================
# Generator Factory 
# ============================================================================

class GeneratorFactory:
    """Factory for creating year-specific validation data generators."""
    
    _generators = {
        2005: CEC2005DataGenerator,
        2006: CEC2006DataGenerator,
        # Add more years as implemented
    }
    
    @classmethod
    def create_generator(cls, config: CECConfig, gen_config: GenerationConfig) -> ValidationDataGenerator:
        """Create appropriate generator for the CEC year."""
        generator_class = cls._generators.get(config.year)
        if not generator_class:
            raise ValueError(f"No generator implemented for CEC{config.year}")
            
        return generator_class(config, gen_config)


# ============================================================================
# Data Management
# ============================================================================

class ValidationDataManager:
    """Handles validation data file operations and safety features."""
    
    def __init__(self, config: CECConfig, gen_config: GenerationConfig):
        self.config = config
        self.gen_config = gen_config
        self.output_dir = Path(config.validation_dir)
        
    def backup_existing_data(self) -> Optional[Path]:
        """Create backup of existing validation data."""
        if not self.output_dir.exists():
            return None
            
        backup_dir = self.output_dir.parent / f"{self.output_dir.name}_backup_{datetime.now().strftime('%Y%m%d_%H%M%S')}"
        
        print(f"Creating backup: {backup_dir}")
        shutil.copytree(self.output_dir, backup_dir)
        
        return backup_dir
    
    def save_validation_data(self, data: Dict[str, Any]) -> None:
        """Save validation data to files."""
        self.output_dir.mkdir(parents=True, exist_ok=True)
        
        for func_key, func_data in data.items():
            output_file = self.output_dir / f"{func_key}.json"
            
            print(f"Saving {output_file}")
            with open(output_file, 'w') as f:
                json.dump(func_data, f, indent=2)
    
    def compare_with_existing(self, new_data: Dict[str, Any]) -> Dict[str, List[str]]:
        """Compare new data with existing validation data."""
        differences = {}
        
        for func_key, new_func_data in new_data.items():
            existing_file = self.output_dir / f"{func_key}.json"
            
            if existing_file.exists():
                with open(existing_file, 'r') as f:
                    existing_data = json.load(f)
                    
                func_diffs = []
                
                # Compare dimensions and test results
                for dim_key, new_dim_data in new_func_data.get("dimensions", {}).items():
                    if dim_key in existing_data.get("dimensions", {}):
                        existing_dim_data = existing_data["dimensions"][dim_key]
                        
                        for test_type, new_result in new_dim_data.get("results", {}).items():
                            if test_type in existing_dim_data.get("results", {}):
                                existing_result = existing_dim_data["results"][test_type]
                                
                                # Compare objective values
                                new_val = new_result.get("objective_value", 0)
                                existing_val = existing_result.get("objective_value", 0)
                                
                                if abs(new_val - existing_val) > 1e-10:
                                    func_diffs.append(
                                        f"Dim {dim_key}, {test_type}: {existing_val} -> {new_val}"
                                    )
                
                if func_diffs:
                    differences[func_key] = func_diffs
        
        return differences


# ============================================================================
# Main Entry Point
# ============================================================================

def main():
    """Main entry point for validation data generation."""
    parser = argparse.ArgumentParser(
        description="Generate CEC Benchmark Validation Data",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__
    )
    
    parser.add_argument(
        "--year",
        type=int, 
        required=True,
        choices=[2005, 2006],
        help="CEC competition year"
    )
    parser.add_argument(
        "--func",
        type=int,
        nargs='+', 
        metavar="ID",
        help="Function IDs to generate data for"
    )
    parser.add_argument(
        "--dim",
        type=int,
        nargs='+',
        help="Dimensions to generate data for" 
    )
    parser.add_argument(
        "--regenerate",
        action="store_true",
        help="Regenerate all data (creates backup)"
    )
    parser.add_argument(
        "--no-backup",
        action="store_true", 
        help="Skip creating backup of existing data"
    )
    parser.add_argument(
        "--no-validate",
        action="store_true",
        help="Skip validation of generated data"
    )
    parser.add_argument(
        "--base-dir",
        default=".",
        help="Base directory for CEC implementations"
    )
    
    args = parser.parse_args()
    
    try:
        # Get configuration 
        config = get_cec_config(args.year, args.base_dir)
        gen_config = GenerationConfig(
            backup_existing=not args.no_backup,
            validate_generated=not args.no_validate
        )
        
        # Create generator and data manager
        generator = GeneratorFactory.create_generator(config, gen_config)
        data_manager = ValidationDataManager(config, gen_config)
        
        # Create backup if requested
        backup_dir = None
        if gen_config.backup_existing and args.regenerate:
            backup_dir = data_manager.backup_existing_data()
        
        # Generate validation data
        print(f"\nGenerating validation data for CEC{args.year}")
        validation_data = generator.generate_validation_data(args.func, args.dim)
        
        # Compare with existing data
        if gen_config.compare_with_existing:
            differences = data_manager.compare_with_existing(validation_data)
            if differences:
                print("\nDifferences detected:")
                for func_key, diffs in differences.items():
                    print(f"  {func_key}:")
                    for diff in diffs:
                        print(f"    {diff}")
        
        # Save generated data
        data_manager.save_validation_data(validation_data)
        
        print(f"\nValidation data generation completed successfully!")
        print(f"Generated data for {len(validation_data)} functions")
        
        if backup_dir:
            print(f"Backup created at: {backup_dir}")
            
    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()