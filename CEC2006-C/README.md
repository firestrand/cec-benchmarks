# CEC2006 Constrained Optimization Benchmark

This directory contains the C implementation of the CEC2006 constrained optimization benchmark suite, consisting of 24 test problems with various constraint types.

## Problem Set

The CEC2006 benchmark includes 24 constrained optimization problems (g01-g24) with:
- Inequality constraints: g(x) ≤ 0
- Equality constraints: h(x) = 0
- Various problem dimensions (2 to 24 variables)

### Problem Specifications

| Problem | Variables | Inequality | Equality | Description |
|---------|-----------|------------|----------|-------------|
| g01 | 13 | 9 | 0 | Quadratic function with linear constraints |
| g02 | n (≥2) | 2 | 0 | Maximization of cos^4 terms (converted to minimization) |
| g03 | n (≥2) | 0 | 1 | Product maximization (converted to minimization) |
| g04 | 5 | 6 | 0 | Quadratic function |
| g05 | 4 | 2 | 3 | Cubic and quadratic terms |
| g06 | 2 | 2 | 0 | Cubic function |
| g07 | 10 | 8 | 0 | Complex nonlinear function |
| g08 | 2 | 2 | 0 | Maximization problem (converted) |
| g09 | 7 | 4 | 0 | Polynomial function |
| g10 | 8 | 6 | 0 | Linear function |
| g11 | 2 | 0 | 1 | Quadratic with equality constraint |
| g12 | 3 | 1 | 0 | Maximization over discrete points |
| g13 | 5 | 0 | 3 | Exponential product |
| g14 | 10 | 0 | 3 | Nonlinear with equality constraints |
| g15 | 3 | 0 | 2 | Quadratic with equalities |
| g16 | 5 | 38 | 0 | Many inequality constraints |
| g17 | 6 | 0 | 4 | Trigonometric problem |
| g18 | 9 | 13 | 0 | Polynomial with many inequalities |
| g19 | 15 | 5 | 0 | Nonlinear objective |
| g20 | 24 | 6 | 14 | Large-scale problem |
| g21 | 7 | 1 | 5 | Mixed constraint types |
| g22 | 22 | 1 | 19 | Large-scale with many equalities |
| g23 | 9 | 2 | 4 | Mixed nonlinear constraints |
| g24 | 2 | 2 | 0 | Simple nonlinear |

## Building

```bash
# Clean and build
make clean
make

# Or just build
make
```

## Usage

```bash
./main <function_id> <dimension> <input_file>
```

- `function_id`: 1-24 (for g01-g24)
- `dimension`: Problem dimension (use -1 for default)
  - For g02 and g03, dimension can be specified
  - Other problems have fixed dimensions
- `input_file`: Text file with one value per line

### Examples

```bash
# Test g01 with zeros (13 variables)
for i in {1..13}; do echo "0.0" >> input.txt; done
./main 1 -1 input.txt

# Test g06 with specific values (2 variables) 
echo "14.095" > input.txt
echo "0.84296" >> input.txt
./main 6 -1 input.txt

# Test g02 with 20 dimensions and random values
for i in {1..20}; do echo "$((RANDOM % 100)).$((RANDOM % 100))" >> input.txt; done
./main 2 20 input.txt
```

## Output Format

The program outputs:
1. Input values
2. Objective function value
3. Constraint values and violations
4. Total constraint violation (sum of all violations)

Example output:
```
Running function G06 with 2 variables
x[1] = 14.095000
x[2] = 0.842960

Objective value = -6.961813875580100E+03

Inequality constraints (g <= 0):
g[1] = -8.882361847289942E-09
g[2] = -8.496240000001151E-01

All constraints satisfied.
```

## Original Source

The original code was developed by Thomas Philip Runarsson (tpr@hi.is) in 2005 for the CEC2006 Special Session on Constrained Real-Parameter Optimization.

## Modifications

- Added standalone `main.c` driver for command-line interface
- Fixed uninitialized variable warnings in g17
- Created Makefile for easy compilation
- Removed dependency on MATLAB MEX and dynamic library loading for standalone usage

## Notes

- Problems g02, g03, g08, and g12 were originally maximization problems but have been converted to minimization
- The benchmark includes a wide variety of constraint types and problem characteristics
- Some problems have very narrow feasible regions or disconnected feasible spaces