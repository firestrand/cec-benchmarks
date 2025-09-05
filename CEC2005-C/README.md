# CEC2005 C Implementation

This directory contains the C implementation of the CEC2005 benchmark functions. The code has been refactored to improve maintainability and follows a standardized approach to file naming and organization.

## Code Refactoring

The original CEC2005 C implementation used preprocessor directives (`#ifdef` statements) to select which benchmark function to compile. This made the code difficult to maintain and required recompilation for each function. The refactored implementation:

1. **Runtime Function Selection**: All 25 functions are compiled into a single executable, with function selection at runtime
2. **Modular Organization**: Each function has its own initialization and calculation functions with consistent naming:
   - `initialize_f1()`, `initialize_f2()`, ... for setup
   - `calc_benchmark_f1()`, `calc_benchmark_f2()`, ... for evaluation
3. **Improved Encapsulation**: Function-specific global variables are properly managed in the `benchmark_data.c` file
4. **Standardized Entry Points**: The `main.c` file provides a unified interface for all functions

## Data File Structure

The input data files for the benchmark functions are organized according to the CEC Benchmark Constant-File Standard:

```
input_data/
├── meta_2005.json    # Unified manifest for all functions
└── f{XX}/            # One folder per benchmark function (f01-f25)
    ├── shift_D50.txt # Shift vector (maximum dimension)
    ├── rot_D2.txt    # Rotation matrix for D=2
    ├── rot_D10.txt   # Rotation matrix for D=10
    ├── rot_D30.txt   # Rotation matrix for D=30
    ├── rot_D50.txt   # Rotation matrix for D=50
    └── ...
```

### Special Cases

- **Function 12**: Uses `bias_D50.txt` which combines alpha, a, and b matrices
- **Function 22**: Uses `rot_sub_D*.txt` for high condition number matrices

### File Naming Convention

Files follow a standardized naming pattern:

```
{DATATYPE}{VARIANT}_D{DIMENSION}.txt
```

Where:
- `DATATYPE`: The type of data (shift, rot, bias, etc.)
- `VARIANT`: Optional qualifier (_sub for sub-component, etc.)
- `DIMENSION`: The vector/matrix dimension (2, 10, 30, 50)

### File Format

Each data file begins with a standardized header comment:

```
# CEC2005 • f01 • shift vector • dim 50
```

This ensures files remain identifiable even when moved outside their directory structure.

### Metadata

Two metadata files provide structured information about the benchmark suite:

1. **`input_data/meta_2005.json`**: Implementation-specific metadata for data file paths
2. **`../metadata/cec2005_function_metadata.json`**: Complete benchmark function properties including:
   - Function names and IDs
   - Properties (shifted, rotated, biased, etc.)
   - Global optimum values
   - Search ranges
   - Characteristics (unimodal, multimodal, separable, etc.)
   - Required data files

## Building and Running

### Compiling
```bash
make clean && make
```

### Running a specific function
```bash
./main <function_id> <dimension> [input_file]
```

Example:
```bash
./main 1 10 test_input.txt
```

### Using the Validation Framework

```bash
cd ..
# Validate all CEC2005 functions
python utility_scripts/validate_cec.py --year 2005

# Validate specific functions
python utility_scripts/validate_cec.py --year 2005 --func 1 4 17

# Validate specific dimensions and test types
python utility_scripts/validate_cec.py --year 2005 --dim 10 30 --type optimal
```

This validates that each function works properly at all supported dimensions (2, 10, 30, 50) and compares against pre-generated validation data.

## Original Data Files

The original data files are preserved in the `input_data_original` directory for reference. The conversion scripts in the `utility_scripts` directory were used to transform these files to the new standardized format.

## Implementation Benefits

1. **Improved Maintainability**: Clean separation of functions and data
2. **Consistent Interface**: All functions use the same calling convention
3. **Simplified Debugging**: Each function can be tested independently
4. **Enhanced Documentation**: Metadata provides clear specifications
5. **Better Organization**: Standardized file structure and naming conventions 