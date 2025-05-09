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
