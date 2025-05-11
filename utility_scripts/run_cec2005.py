#!/usr/bin/env python3
"""
CEC2005 Benchmark Helper Script

This script runs the CEC2005 benchmark programs with various input vectors to test
functionality and generate validation data.

Usage:
  python run_cec2005.py --all           # Run all functions with all dimensions
  python run_cec2005.py --func N        # Run specific function N with all dimensions
  python run_cec2005.py --dim D         # Run all functions with dimension D
  python run_cec2005.py --func N --dim D # Run specific function N with dimension D
  python run_cec2005.py --type TYPE     # Use specific input type (zeros, random, etc.)
  python run_cec2005.py --validate      # Generate validation dataset for all functions/dimensions
"""

import os
import sys
import json
import argparse
import subprocess
import tempfile
import datetime
import random

# Path to the CEC2005 benchmark directory
CEC2005_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '../CEC2005-C'))
RESULTS_DIR = os.path.join(CEC2005_DIR, 'results')
VALIDATION_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '../validation_data/CEC2005'))

# Supported dimensions
DIMENSIONS = [2, 10, 30, 50]

# Supported functions
FUNCTIONS = list(range(1, 26))  # Functions 1-25

# Default search bounds for CEC2005 functions
DEFAULT_BOUNDS = (-100.0, 100.0)  # Most functions have these bounds

# Load function metadata
def load_metadata():
    """Load function metadata from meta_2005.json"""
    meta_file = os.path.join(CEC2005_DIR, 'input_data', 'meta_2005.json')
    if os.path.exists(meta_file):
        with open(meta_file, 'r') as f:
            return json.load(f)
    return None

def load_shift_vector(func_id, dimension, meta=None):
    """Load the shift vector for a function (which is the global optimum for most functions).
    
    Args:
        func_id: Function ID (1-25)
        dimension: Number of variables (2, 10, 30, 50)
        meta: Metadata with function information
        
    Returns:
        List of shift vector values or None if not found
    """
    if not meta:
        return None
        
    func_key = f"f{func_id:02d}"
    if func_key not in meta.get('functions', {}):
        return None
        
    func_meta = meta['functions'][func_key]
    if 'files' not in func_meta or 'shift' not in func_meta['files']:
        return None
        
    shift_file = os.path.join(CEC2005_DIR, 'input_data', func_meta['files']['shift'])
    if not os.path.exists(shift_file):
        return None
        
    shift_vector = []
    
    with open(shift_file, 'r') as sf:
        for line in sf:
            # Process space-delimited values (common format in CEC2005)
            parts = line.strip().split()
            for part in parts:
                try:
                    val = float(part)
                    shift_vector.append(val)
                    if len(shift_vector) >= dimension:
                        break
                except ValueError:
                    # Skip values that can't be converted to floats
                    continue
            
            # Break if we have enough values
            if len(shift_vector) >= dimension:
                break
                
    return shift_vector[:dimension] if shift_vector else None

def create_input_file(dimension, input_type='zeros', func_id=None, meta=None):
    """Create a temporary input file with specified values.
    
    Args:
        dimension: Number of variables (2, 10, 30, or 50)
        input_type: Type of input values ('zeros', 'random', 'min', 'max', 'optimal')
        func_id: Function ID for optimal value retrieval (1-25)
        meta: Metadata with function information
        
    Returns:
        Tuple of (path to created temporary file, input vector)
    """
    _, input_file = tempfile.mkstemp(suffix='.txt')
    input_vector = []
    
    # Get bounds if available
    bounds = DEFAULT_BOUNDS
    if meta and func_id:
        func_key = f"f{func_id:02d}"
        if func_key in meta.get('functions', {}):
            func_meta = meta['functions'][func_key]
            if 'bounds' in func_meta:
                bounds = (func_meta['bounds']['min'], func_meta['bounds']['max'])
    
    with open(input_file, 'w') as f:
        if input_type == 'zeros':
            for _ in range(dimension):
                f.write("0.0\n")
                input_vector.append(0.0)
        elif input_type == 'random':
            for _ in range(dimension):
                # Generate random values between bounds
                val = random.uniform(bounds[0], bounds[1])
                f.write(f"{val}\n")
                input_vector.append(val)
        elif input_type == 'min':
            # Use lower bound for all variables
            for _ in range(dimension):
                f.write(f"{bounds[0]}\n")
                input_vector.append(bounds[0])
        elif input_type == 'max':
            # Use upper bound for all variables
            for _ in range(dimension):
                f.write(f"{bounds[1]}\n")
                input_vector.append(bounds[1])
        elif input_type == 'optimal':
            # Special cases for functions that have modified optimal inputs
            if func_id == 5:
                # For F5, create a special input based on the shift vector
                shift_vector = load_shift_vector(func_id, dimension, meta)
                if shift_vector and len(shift_vector) >= dimension:
                    # Create a modified input with some values at bounds
                    for i in range(dimension):
                        if i < dimension // 4:
                            val = -100.0  # Set first quarter to lower bound
                        elif i >= 3 * dimension // 4:
                            val = 100.0   # Set last quarter to upper bound
                        else:
                            val = shift_vector[i]  # Use shift vector for middle values
                        f.write(f"{val}\n")
                        input_vector.append(val)
                else:
                    # Fallback to zeros
                    for _ in range(dimension):
                        f.write("0.0\n")
                        input_vector.append(0.0)
            elif func_id == 8:
                # For F8, create input based on shift vector but with modified values
                shift_vector = load_shift_vector(func_id, dimension, meta)
                if shift_vector and len(shift_vector) >= dimension:
                    # Create a modified input with some values at -32
                    for i in range(dimension):
                        if i % 2 == 0 and i // 2 < dimension // 2:
                            val = -32.0  # Set even indices to -32 for half the vector
                        else:
                            val = shift_vector[i]
                        f.write(f"{val}\n")
                        input_vector.append(val)
                else:
                    # Fallback to zeros
                    for _ in range(dimension):
                        f.write("0.0\n")
                        input_vector.append(0.0)
            elif func_id == 12:
                # For F12, the optimal input is alpha_f12, not the shift vector
                # Since we don't have direct access to alpha_f12, we'll use zeros as fallback
                # Using zeros gives poor results, but it's a limitation of this approach
                for _ in range(dimension):
                    f.write("0.0\n")
                    input_vector.append(0.0)
            elif func_id == 20:
                # For F20, create input based on shift vector but with modified values
                shift_vector = load_shift_vector(func_id, dimension, meta)
                if shift_vector and len(shift_vector) >= dimension:
                    # Create a modified input with odd indices at 5.0
                    for i in range(dimension):
                        if i % 2 == 1 and i // 2 < dimension // 2:
                            val = 5.0  # Set odd indices to 5 for half the vector
                        else:
                            val = shift_vector[i]
                        f.write(f"{val}\n")
                        input_vector.append(val)
                else:
                    # Fallback to zeros
                    for _ in range(dimension):
                        f.write("0.0\n")
                        input_vector.append(0.0)
            else:
                # For most CEC2005 functions, the shift vector is the input that produces the optimal value
                # This is because x-o becomes 0 when x=o, resulting in the bias value
                shift_vector = load_shift_vector(func_id, dimension, meta)
                
                if shift_vector and len(shift_vector) >= dimension:
                    # Use the shift vector as input (optimal)
                    for i in range(dimension):
                        f.write(f"{shift_vector[i]}\n")
                        input_vector.append(shift_vector[i])
                else:
                    # If no shift vector available, use zeros as fallback
                    # Note: This will not give the optimal value for shifted functions
                    for _ in range(dimension):
                        f.write("0.0\n")
                        input_vector.append(0.0)
        else:
            raise ValueError(f"Unsupported input type: {input_type}")
    
    return input_file, input_vector

def run_benchmark(func_id, dimension, input_file, log_file=None):
    """Run the CEC2005 benchmark with specified parameters.
    
    Args:
        func_id: Function ID (1-25)
        dimension: Number of variables (2, 10, 30, or 50)
        input_file: Path to input file containing variable values
        log_file: Path to log file to save output
        
    Returns:
        Output of the benchmark run
    """
    cmd = [
        os.path.join(CEC2005_DIR, 'main'),
        str(func_id),
        str(dimension),
        input_file
    ]
    
    print(f"Running: Function F{func_id} with {dimension} dimensions")
    
    try:
        result = subprocess.run(
            cmd, 
            stdout=subprocess.PIPE, 
            stderr=subprocess.PIPE,
            universal_newlines=True,
            cwd=CEC2005_DIR
        )
        
        # Save output to log file if specified
        if log_file:
            with open(log_file, 'a') as f:
                f.write(f"\n\n{'='*40}\n")
                f.write(f"Function F{func_id} with {dimension} dimensions\n")
                f.write(f"Input type: {os.path.basename(input_file)}\n")
                f.write(f"Date: {datetime.datetime.now()}\n")
                f.write(f"{'='*40}\n\n")
                
                if result.stdout:
                    f.write(result.stdout)
                if result.stderr:
                    f.write("\nERRORS:\n")
                    f.write(result.stderr)
                
                f.write(f"\n\nExit code: {result.returncode}\n")
        
        if result.returncode != 0:
            print(f"Error running benchmark: {result.stderr}")
            return None
        
        return result.stdout
    except Exception as e:
        print(f"Exception while running benchmark: {e}")
        return None

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
                    return parts[1].strip()
    
    return None

def generate_validation_data_for_function(func_id, dimensions, meta=None):
    """Generate validation data for a specific function across all specified dimensions.
    
    Args:
        func_id: Function ID (1-25)
        dimensions: List of dimensions to validate
        meta: Function metadata
        
    Returns:
        Dictionary containing validation data
    """
    func_key = f"f{func_id:02d}"
    function_name = f"Function {func_id}"
    
    # Get function name from metadata if available
    if meta and func_key in meta.get('functions', {}):
        function_name = meta['functions'][func_key].get('name', function_name)
    
    validation_data = {
        "function_id": func_id,
        "function_name": function_name,
        "date_generated": datetime.datetime.now().isoformat(),
        "dimensions": {}
    }
    
    # Define input types to test
    input_types = ['min', 'max', 'optimal', 'random']
    
    for dimension in dimensions:
        print(f"Generating validation data for F{func_id} in {dimension} dimensions...")
        
        dimension_data = {
            "results": {}
        }
        
        for input_type in input_types:
            print(f"  - Processing {input_type} input...")
            
            # Create input file
            input_file, input_vector = create_input_file(dimension, input_type, func_id, meta)
            
            try:
                # Run benchmark
                output = run_benchmark(func_id, dimension, input_file)
                
                # Extract objective value
                obj_value = extract_objective_value(output)
                
                # Store result
                dimension_data["results"][input_type] = {
                    "input_vector": input_vector,
                    "objective_value": obj_value
                }
            finally:
                # Clean up
                if os.path.exists(input_file):
                    os.unlink(input_file)
        
        # Add dimension data to validation data
        validation_data["dimensions"][str(dimension)] = dimension_data
    
    return validation_data

def save_validation_data(validation_data, func_id):
    """Save validation data to a JSON file.
    
    Args:
        validation_data: Dictionary containing validation data
        func_id: Function ID (1-25)
        
    Returns:
        Path to the saved file
    """
    # Create validation directory if it doesn't exist
    if not os.path.exists(VALIDATION_DIR):
        os.makedirs(VALIDATION_DIR)
    
    # Create filename - one file per function with all dimensions
    filename = f"f{func_id:02d}.json"
    filepath = os.path.join(VALIDATION_DIR, filename)
    
    # Save file
    with open(filepath, 'w') as f:
        json.dump(validation_data, f, indent=2)
    
    print(f"Saved validation data to {filepath}")
    return filepath

def main():
    parser = argparse.ArgumentParser(description='Run CEC2005 benchmarks with various inputs')
    parser.add_argument('--func', type=int, help='Function ID (1-25)')
    parser.add_argument('--dim', type=int, choices=DIMENSIONS, help='Problem dimension')
    parser.add_argument('--type', default='zeros', choices=['zeros', 'random', 'min', 'max', 'optimal'], help='Input vector type')
    parser.add_argument('--all', action='store_true', help='Run all functions with all dimensions')
    parser.add_argument('--log', action='store_true', help='Save output to log files')
    parser.add_argument('--validate', action='store_true', help='Generate validation data for specified functions/dimensions')
    
    args = parser.parse_args()
    
    # Load metadata
    meta = load_metadata()
    
    # Create results directory if it doesn't exist
    if args.log and not os.path.exists(RESULTS_DIR):
        os.makedirs(RESULTS_DIR)
    
    # Determine which functions to run
    if args.func is not None:
        if args.func < 1 or args.func > 25:
            print(f"Error: Function ID must be between 1 and 25, got {args.func}")
            return 1
        functions = [args.func]
    else:
        functions = FUNCTIONS
    
    # Determine which dimensions to run
    if args.dim is not None:
        dimensions = [args.dim]
    else:
        dimensions = DIMENSIONS
    
    # Handle validation data generation
    if args.validate:
        print(f"Generating validation data for {len(functions)} functions across {len(dimensions)} dimensions...")
        
        for func_id in functions:
            validation_data = generate_validation_data_for_function(func_id, dimensions, meta)
            save_validation_data(validation_data, func_id)
        
        print("Validation data generation complete!")
        return 0
    
    # Run benchmarks
    success_count = 0
    total_count = 0
    results = []
    
    timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
    summary_log = os.path.join(RESULTS_DIR, f"summary_{args.type}_{timestamp}.txt")
    
    for func_id in functions:
        for dimension in dimensions:
            total_count += 1
            
            # Create input file
            input_file, _ = create_input_file(dimension, args.type, func_id, meta)
            
            try:
                # Create log file name if logging is enabled
                log_file = None
                if args.log:
                    log_file = os.path.join(RESULTS_DIR, f"f{func_id:02d}_D{dimension}_{args.type}_{timestamp}.log")
                
                # Run benchmark
                output = run_benchmark(func_id, dimension, input_file, log_file)
                
                # Process output
                if output:
                    print(output)
                    print("-" * 40)
                    
                    # Extract and save objective value
                    obj_value = extract_objective_value(output)
                    results.append({
                        'function': func_id,
                        'dimension': dimension,
                        'input_type': args.type,
                        'objective_value': obj_value
                    })
                    
                    success_count += 1
            finally:
                # Clean up
                if os.path.exists(input_file):
                    os.unlink(input_file)
    
    # Save summary to file
    if args.log:
        with open(summary_log, 'w') as f:
            f.write(f"CEC2005 Benchmark Summary\n")
            f.write(f"Date: {datetime.datetime.now()}\n")
            f.write(f"Input type: {args.type}\n\n")
            f.write(f"{'Function':<10} {'Dimension':<10} {'Objective Value':<25}\n")
            f.write(f"{'-'*45}\n")
            
            for result in results:
                f.write(f"F{result['function']:<9} {result['dimension']:<10} {result['objective_value']:<25}\n")
            
            f.write(f"\nSuccessfully ran {success_count} of {total_count} benchmark configurations\n")
    
    print(f"Successfully ran {success_count} of {total_count} benchmark configurations")
    return 0 if success_count == total_count else 1

if __name__ == "__main__":
    sys.exit(main()) 