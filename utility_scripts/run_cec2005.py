#!/usr/bin/env python3
"""
CEC2005 Benchmark Helper Script

This script runs the CEC2005 benchmark programs with various input vectors to test
functionality and generate validation data.

Usage:
  python run_cec2005.py --all          # Run all functions with all dimensions
  python run_cec2005.py --func N       # Run specific function N with all dimensions
  python run_cec2005.py --dim D        # Run all functions with dimension D
  python run_cec2005.py --func N --dim D # Run specific function N with dimension D
  python run_cec2005.py --type TYPE    # Use specific input type (zeros, random, etc.)
"""

import os
import sys
import argparse
import subprocess
import tempfile
import datetime

# Path to the CEC2005 benchmark directory
CEC2005_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '../CEC2005-C'))
RESULTS_DIR = os.path.join(CEC2005_DIR, 'results')

# Supported dimensions
DIMENSIONS = [2, 10, 30, 50]

# Supported functions
FUNCTIONS = list(range(1, 26))  # Functions 1-25

def create_input_file(dimension, input_type='zeros'):
    """Create a temporary input file with specified values.
    
    Args:
        dimension: Number of variables (2, 10, 30, or 50)
        input_type: Type of input values ('zeros', 'random', etc.)
        
    Returns:
        Path to the created temporary file
    """
    _, input_file = tempfile.mkstemp(suffix='.txt')
    
    with open(input_file, 'w') as f:
        if input_type == 'zeros':
            for _ in range(dimension):
                f.write("0.0\n")
        elif input_type == 'random':
            import random
            for _ in range(dimension):
                # Generate random values between -100 and 100
                f.write(f"{random.uniform(-100.0, 100.0)}\n")
        else:
            raise ValueError(f"Unsupported input type: {input_type}")
    
    return input_file

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
                return parts[1].strip()
    
    return None

def main():
    parser = argparse.ArgumentParser(description='Run CEC2005 benchmarks with various inputs')
    parser.add_argument('--func', type=int, help='Function ID (1-25)')
    parser.add_argument('--dim', type=int, choices=DIMENSIONS, help='Problem dimension')
    parser.add_argument('--type', default='zeros', choices=['zeros', 'random'], help='Input vector type')
    parser.add_argument('--all', action='store_true', help='Run all functions with all dimensions')
    parser.add_argument('--log', action='store_true', help='Save output to log files')
    
    args = parser.parse_args()
    
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
            input_file = create_input_file(dimension, args.type)
            
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