# CEC Benchmark Validation Framework

A unified validation framework for all CEC (Congress on Evolutionary Computation) benchmark functions across different competition years (2005-2009).

## Features

- **Generic Architecture**: Single validation framework that works across all CEC years
- **Strategy Pattern**: Year-specific executors handle implementation differences
- **Comprehensive Testing**: Supports multiple test types (min, max, optimal, random, etc.)
- **Smart Tolerances**: Adaptive tolerance based on value magnitude and function type
- **Noisy Function Support**: Special handling for stochastic functions

## Usage

### Basic Commands

```bash
# Validate all functions for a specific year
python validate_cec.py --year 2005

# Validate specific functions
python validate_cec.py --year 2005 --func 1 4 17

# Validate specific dimensions
python validate_cec.py --year 2005 --dim 10 30

# Validate specific test types
python validate_cec.py --year 2005 --type optimal

# Combine options
python validate_cec.py --year 2005 --func 4 --dim 10 --type optimal random
```

### Shell Script Helper

```bash
# Using the convenience script
./run_cec_validation.sh --year 2005
./run_cec_validation.sh --year 2005 --func 1 --dim 10
```

## Architecture

### Component Overview

```
CECValidator (Main Orchestrator)
├── CECConfig (Configuration per year)
├── FunctionExecutor (Abstract base)
│   ├── CEC2005Executor (C implementation)
│   ├── CEC2006Executor (Java/MATLAB - future)
│   └── ... (other years)
├── ToleranceChecker (Validation logic)
├── ValidationReporter (Output formatting)
└── ExecutorFactory (Strategy pattern)
```

### Key Components

- **CECValidator**: Main validation orchestrator
- **FunctionExecutor**: Abstract base class for year-specific implementations
- **ExecutorFactory**: Creates appropriate executor based on year
- **ToleranceChecker**: Handles tolerance checking with adaptive thresholds
- **ValidationReporter**: Consistent output formatting across years

## Tolerance Settings

### Deterministic Functions

| Value Range | Absolute Tolerance | Relative Tolerance |
|------------|-------------------|-------------------|
| < 10^4 | 1e-6 | 1e-9 |
| 10^4 - 10^6 | 1.0 | 1e-5 |
| 10^6 - 10^9 | 1e5 | 1e-4 |
| > 10^9 | 1e-3 | 1e-8 |

### Noisy Functions

- **Optimal values**: Strict tolerance (same as deterministic)
- **Other test types**: 
  - Relative tolerance: 50%
  - Magnitude check: 0.1x to 10x of expected value
  - Note: Due to random noise, occasional validation failures are expected

## Supported Years

### CEC2005 ✅
- 25 benchmark functions
- C implementation
- Dimensions: 2, 10, 30, 50
- Noisy functions: F4, F17, F24, F25

### CEC2006 (Future)
- 24 constrained optimization problems
- Java/MATLAB implementation
- To be implemented

### CEC2007-2009 (Future)
- Various problem sets
- To be implemented

## Adding Support for New Years

To add support for a new CEC year:

1. Create an executor class:
```python
class CEC20XXExecutor(FunctionExecutor):
    def build(self) -> bool:
        # Implementation-specific build
    
    def run(self, func_id, dimension, input_vector) -> float:
        # Execute function and return value
    
    def cleanup(self) -> None:
        # Cleanup resources
```

2. Register in ExecutorFactory:
```python
_executors = {
    2005: CEC2005Executor,
    20XX: CEC20XXExecutor,  # Add your year
}
```

3. Add configuration in `get_cec_config()`:
```python
20XX: CECConfig(
    year=20XX,
    implementation_dir=f"{base_dir}/CEC20XX",
    validation_dir=f"{base_dir}/validation_data/CEC20XX",
    metadata_path=f"{base_dir}/CEC20XX/input_data/meta_20XX.json",
    num_functions=XX,
    supported_dimensions=[...],
    default_test_types=[...]
)
```

## Exit Codes

- `0`: All validations passed
- `1`: One or more validations failed

## Requirements

- Python 3.6+
- NumPy
- C compiler (for CEC2005)
- Java/MATLAB (for CEC2006, when implemented)

## Notes

- The framework is designed to be extensible for future CEC competitions
- Validation data must be pre-generated and stored in `validation_data/CEC{YEAR}/`
- Metadata must follow the standard format in `input_data/meta_{year}.json`
- For noisy functions, multiple runs may produce slightly different results due to randomness