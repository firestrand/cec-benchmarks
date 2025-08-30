#!/usr/bin/env python3
"""
CEC2005 Validation Script

This script validates the CEC2005 implementation against the golden dataset.
It runs each function with the same inputs as stored in the validation data
and compares the outputs to ensure consistency.

Usage:
  python validate_cec2005.py           # Validate all functions
  python validate_cec2005.py --func N  # Validate specific function N
  python validate_cec2005.py --dim D   # Validate specific dimension D
  python validate_cec2005.py --verbose # Show detailed output
"""

import os
import sys
import json
import argparse
import subprocess
import tempfile
import math
from pathlib import Path

# Path to the CEC2005 benchmark directory
CEC2005_DIR = Path(__file__).parent.parent / 'CEC2005-C'
VALIDATION_DIR = Path(__file__).parent.parent / 'validation_data' / 'CEC2005'

# Supported dimensions
DIMENSIONS = [2, 10, 30, 50]

# Supported functions
FUNCTIONS = list(range(1, 26))  # Functions 1-25

# Tolerance for floating point comparison
# F4, F17, and F24 have noise, so they need higher tolerance
NOISE_FUNCTIONS = [4, 17, 24]
DEFAULT_TOLERANCE = 1e-6
NOISE_TOLERANCE = 1.0  # Higher tolerance for noisy functions

def build_benchmark():
    """Build the CEC2005 benchmark if needed"""
    main_path = CEC2005_DIR / 'main'
    if not main_path.exists():
        print("Building CEC2005 benchmark...")
        result = subprocess.run(
            ['make', 'clean'],
            cwd=CEC2005_DIR,
            capture_output=True,
            text=True
        )
        result = subprocess.run(
            ['make'],
            cwd=CEC2005_DIR,
            capture_output=True,
            text=True
        )
        if result.returncode != 0:
            print(f"Error building benchmark: {result.stderr}")
            return False
    return True

def create_input_file(input_vector):
    """Create a temporary input file with specified values"""
    _, input_file = tempfile.mkstemp(suffix='.txt')
    
    with open(input_file, 'w') as f:
        for value in input_vector:
            f.write(f"{value}\n")
    
    return input_file

def run_benchmark(func_id, dimension, input_file):
    """Run the CEC2005 benchmark with specified parameters"""
    cmd = [
        str(CEC2005_DIR / 'main'),
        str(func_id),
        str(dimension),
        input_file
    ]
    
    try:
        result = subprocess.run(
            cmd,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            cwd=CEC2005_DIR
        )
        
        if result.returncode != 0:
            return None, result.stderr
        
        return result.stdout, None
    except Exception as e:
        return None, str(e)

def extract_objective_value(output):
    """Extract the objective value from the benchmark output"""
    if output is None:
        return None
    
    for line in output.splitlines():
        if "Objective value" in line:
            parts = line.split('=')
            if len(parts) > 1:
                try:
                    return float(parts[1].strip())
                except ValueError:
                    return None
    
    return None

def compare_values(expected, actual, func_id):
    """Compare two objective values with appropriate tolerance"""
    if expected is None or actual is None:
        return False
    
    # Use higher tolerance for functions with noise
    tolerance = NOISE_TOLERANCE if func_id in NOISE_FUNCTIONS else DEFAULT_TOLERANCE
    
    # Handle special cases
    if math.isinf(expected) and math.isinf(actual):
        return True
    if math.isnan(expected) and math.isnan(actual):
        return True
    
    # Calculate relative error
    if abs(expected) > 1e-10:
        relative_error = abs((actual - expected) / expected)
        return relative_error < tolerance
    else:
        # For values close to zero, use absolute error
        return abs(actual - expected) < tolerance

def validate_function(func_id, dimensions=None, verbose=False):
    """Validate a specific function across specified dimensions"""
    validation_file = VALIDATION_DIR / f"f{func_id:02d}.json"
    
    if not validation_file.exists():
        print(f"  ❌ Validation data not found for F{func_id}")
        return False, {}
    
    with open(validation_file, 'r') as f:
        validation_data = json.load(f)
    
    if dimensions is None:
        dimensions = DIMENSIONS
    
    results = {
        'function_id': func_id,
        'function_name': validation_data.get('function_name', f'Function {func_id}'),
        'dimensions': {},
        'total_tests': 0,
        'passed_tests': 0,
        'failed_tests': 0
    }
    
    print(f"\nValidating F{func_id}: {results['function_name']}")
    
    for dim in dimensions:
        dim_key = str(dim)
        if dim_key not in validation_data['dimensions']:
            if verbose:
                print(f"  ⚠️  No validation data for dimension {dim}")
            continue
        
        dim_data = validation_data['dimensions'][dim_key]
        dim_results = {
            'tests': {},
            'passed': 0,
            'failed': 0
        }
        
        print(f"  Dimension {dim}:")
        
        for input_type, test_data in dim_data['results'].items():
            results['total_tests'] += 1
            
            # Create input file
            input_file = create_input_file(test_data['input_vector'])
            
            try:
                # Run benchmark
                output, error = run_benchmark(func_id, dim, input_file)
                
                if error:
                    print(f"    ❌ {input_type:8s}: Error - {error}")
                    dim_results['tests'][input_type] = {'status': 'error', 'error': error}
                    dim_results['failed'] += 1
                    results['failed_tests'] += 1
                else:
                    # Extract objective value
                    actual_value = extract_objective_value(output)
                    expected_value = test_data['objective_value']
                    
                    # Compare values
                    if compare_values(expected_value, actual_value, func_id):
                        status_symbol = "✓"
                        status = 'passed'
                        dim_results['passed'] += 1
                        results['passed_tests'] += 1
                    else:
                        status_symbol = "✗"
                        status = 'failed'
                        dim_results['failed'] += 1
                        results['failed_tests'] += 1
                    
                    dim_results['tests'][input_type] = {
                        'status': status,
                        'expected': expected_value,
                        'actual': actual_value
                    }
                    
                    if verbose or status == 'failed':
                        diff = abs(actual_value - expected_value) if actual_value and expected_value else 'N/A'
                        print(f"    {status_symbol} {input_type:8s}: expected={expected_value:15.6f}, actual={actual_value:15.6f}, diff={diff}")
                    else:
                        print(f"    {status_symbol} {input_type:8s}: {status}")
                    
            finally:
                # Clean up
                if os.path.exists(input_file):
                    os.unlink(input_file)
        
        results['dimensions'][dim_key] = dim_results
    
    # Summary for this function
    success = results['failed_tests'] == 0
    status_symbol = "✅" if success else "❌"
    print(f"  {status_symbol} Summary: {results['passed_tests']}/{results['total_tests']} tests passed")
    
    return success, results

def main():
    parser = argparse.ArgumentParser(description='Validate CEC2005 implementation against golden dataset')
    parser.add_argument('--func', type=int, help='Function ID (1-25) to validate')
    parser.add_argument('--dim', type=int, choices=DIMENSIONS, help='Specific dimension to validate')
    parser.add_argument('--verbose', '-v', action='store_true', help='Show detailed output')
    parser.add_argument('--summary', '-s', action='store_true', help='Show summary only')
    
    args = parser.parse_args()
    
    # Build benchmark if needed
    if not build_benchmark():
        print("Failed to build benchmark")
        return 1
    
    # Determine which functions to validate
    if args.func is not None:
        if args.func < 1 or args.func > 25:
            print(f"Error: Function ID must be between 1 and 25, got {args.func}")
            return 1
        functions = [args.func]
    else:
        functions = FUNCTIONS
    
    # Determine which dimensions to validate
    dimensions = [args.dim] if args.dim else None
    
    # Run validation
    print("="*60)
    print("CEC2005 Validation Against Golden Dataset")
    print("="*60)
    
    all_results = []
    total_functions_passed = 0
    total_functions_failed = 0
    
    for func_id in functions:
        success, results = validate_function(func_id, dimensions, args.verbose)
        all_results.append(results)
        
        if success:
            total_functions_passed += 1
        else:
            total_functions_failed += 1
    
    # Print final summary
    print("\n" + "="*60)
    print("VALIDATION SUMMARY")
    print("="*60)
    
    total_tests = sum(r['total_tests'] for r in all_results)
    total_passed = sum(r['passed_tests'] for r in all_results)
    total_failed = sum(r['failed_tests'] for r in all_results)
    
    print(f"Functions tested: {len(functions)}")
    print(f"Functions passed: {total_functions_passed}")
    print(f"Functions failed: {total_functions_failed}")
    print(f"Total tests run: {total_tests}")
    print(f"Tests passed: {total_passed}")
    print(f"Tests failed: {total_failed}")
    
    if total_failed > 0:
        print("\n⚠️  FAILED FUNCTIONS:")
        for r in all_results:
            if r['failed_tests'] > 0:
                print(f"  - F{r['function_id']}: {r['function_name']} ({r['failed_tests']} tests failed)")
                if not args.summary:
                    for dim_key, dim_results in r['dimensions'].items():
                        if dim_results['failed'] > 0:
                            print(f"    Dimension {dim_key}:")
                            for test_type, test_result in dim_results['tests'].items():
                                if test_result['status'] == 'failed':
                                    exp = test_result.get('expected', 'N/A')
                                    act = test_result.get('actual', 'N/A')
                                    print(f"      - {test_type}: expected={exp}, actual={act}")
    
    if total_functions_passed == len(functions):
        print("\n✅ All functions passed validation!")
        return 0
    else:
        print(f"\n❌ Validation failed: {total_failed} tests failed")
        return 1

if __name__ == "__main__":
    sys.exit(main())