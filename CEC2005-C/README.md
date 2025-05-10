# CEC2005 C Implementation

This directory contains the C implementation of the CEC2005 benchmark functions. The code has been refactored to improve maintainability and follows a standardized approach to file naming and organization.

## Data File Structure

The input data files for the benchmark functions are organized according to the CEC Benchmark Constant-File Standard:

```
input_data/
├── meta_2005.json    # Unified manifest for all functions
└── f{XX}/            # One folder per benchmark function (f01-f25)
    ├── shift_D50.txt # Shift vector (maximum dimension)
    ├── rot_D10.txt   # Rotation matrix for D=10
    ├── rot_D30.txt   # Rotation matrix for D=30
    └── ...
```

### File Naming Convention

Files follow a standardized naming pattern:

```
{DATATYPE}{VARIANT}_D{DIMENSION}.txt
```

Where:
- `DATATYPE`: The type of data (shift, rot, bias, etc.)
- `VARIANT`: Optional qualifier (_nr for no rotation, _sub for sub-component, etc.)
- `DIMENSION`: The vector/matrix dimension (2, 10, 30, 50)

### File Format

Each data file begins with a standardized header comment:

```
# CEC2005 • f01 • shift vector • dim 50
```

This ensures files remain identifiable even when moved outside their directory structure.

### Metadata

The `meta_2005.json` file provides a unified manifest of all benchmark functions, including:
- Function names
- Supported dimensions
- Paths to all data files

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

### Using the Python helper
```bash
cd ..
python utility_scripts/run_cec2005.py --func 1 --dim 10 --type zeros
```

## Testing

To verify all functions with zero inputs:
```bash
cd ..
python utility_scripts/run_all_functions_with_zeros.py
```

## Original Data Files

The original data files are preserved in the `input_data_original` directory for reference. 