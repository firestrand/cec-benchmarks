# CEC Benchmark Repository

## Goal

This repository serves as a centralized and standardized collection of the CEC (Congress on Evolutionary Computation) benchmark functions source code. Some of this code dates back 20 years and may require modifications to build and run on modern systems.

The primary objectives are:

1.  **Preservation and Accessibility**: To download, preserve, and make the original CEC source code readily accessible.
2.  **Build Modernization**: To apply necessary updates to ensure the legacy C code can be compiled and executed.
3.  **Golden Dataset Generation**: To produce a "golden" validation dataset for each benchmark function across all its supported dimensions. This dataset will include outputs for:
    *   Minimum input value
    *   Maximum input value
    *   Optimal (or best-known) input value
    *   A random input value
4.  **Standardization**:
    *   To rename and organize any accompanying constant files according to the conventions outlined in `cec_constant_naming_convention.md`.
    *   To address and rectify inconsistencies found in the original C source code, aiming for improved clarity and maintainability while preserving the original algorithms' integrity.

## Methodology

To achieve these goals, the following steps will be undertaken:

1.  **Source Code Acquisition**: Download the original C source code for various CEC benchmark years.
2.  **Build System Setup**: Establish a consistent build environment, potentially requiring minor modifications to the source code (e.g., header updates, compiler flag adjustments).
3.  **Execution Simplification**:
    *   Minimal changes will be made to the C source code to simplify the execution interface for batch processing and data generation.
    *   A Python helper script, located in the `/utility_scripts` directory, will be developed to automate the process of running the benchmark functions with predefined inputs.
    *   If it simplifies the process, input data files will be created and utilized by the C programs (e.g., via a command-line flag) to specify the exact inputs for which outputs are required.
4.  **Validation Data Generation and Storage**:
    *   The Python script will orchestrate the execution of each CEC function for the specified input scenarios (min, max, optimal, random) across all supported dimensions.
    *   The resulting output data will be captured and stored in JSON format.
    *   The validation datasets will be organized in a `validation_data` directory, sub-structured by year (`CECYEAR`), with individual JSON files for each function and dimension (e.g., `validation_data/CEC2021/f01_D10.json`).
5.  **Constant File Normalization**: All constant files (e.g., shift vectors, rotation matrices) will be renamed and organized according to the specifications in `cec_constant_naming_convention.md`.
6.  **Code Consistency Pass**: Review and apply minimal, targeted changes to the C source code to improve consistency (e.g., variable naming, function signatures where appropriate) without altering the core algorithmic logic.

This structured approach aims to create a reliable and easy-to-use resource for researchers and practitioners working with CEC benchmark functions.

## Example Usage (CEC2005)

This section provides a brief example of how to compile and run one of the CEC2005 benchmark functions.

1.  **Navigate to the CEC2005 directory**:
    ```bash
    cd CEC2005-C
    ```

2.  **Compile the source code**:
    Use the provided `Makefile` to build the executable.
    ```bash
    make
    ```

3.  **Run a benchmark function**:
    Execute the `main` program, specifying the function ID, the number of dimensions, and an input file.
    ```bash
    ./main 1 10 input_file.txt
    ```
    - `1` is the function ID (1-25)
    - `10` is the dimension (2, 10, 30, or 50)
    - `input_file.txt` is a file containing the input vector (one value per line)

4.  **Using the Validation Framework**:
    The repository includes a unified validation framework that works across all CEC years:
    ```bash
    # Validate all CEC2005 functions
    python utility_scripts/validate_cec.py --year 2005
    
    # Validate specific functions
    python utility_scripts/validate_cec.py --year 2005 --func 1 4 17
    
    # Validate specific dimensions and test types
    python utility_scripts/validate_cec.py --year 2005 --dim 10 30 --type optimal
    
    # Use the convenience script
    ./utility_scripts/run_cec_validation.sh --year 2005 --func 1
    ```

## Data File Structure

The data files for the CEC2005 benchmark functions have been refactored to follow a consistent naming convention:

```
CEC2005-C/
└── input_data/
    └── f{FUNC:02d}/    # one folder per benchmark function (f01, f02, etc.)
        ├── shift_D10.txt  # shift vector for dimension 10
        ├── rot_D10.txt    # rotation matrix for dimension 10
        ├── ...
        └── f{FUNC:02d}.meta.yaml  # metadata file describing the function
```

This refactored structure makes it easier to:
1. Locate the appropriate files for each function and dimension
2. Understand the purpose of each file
3. Programmatically access the data files

**Note:** The data files no longer contain metadata comments at the beginning of each file. Instead, all metadata information is stored in the meta_2005.json file in the input_data directory.
