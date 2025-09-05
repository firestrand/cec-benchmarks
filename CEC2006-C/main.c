/*
 * CEC2006 Constrained Optimization Benchmark - Main Driver
 * 
 * This program provides a command-line interface to the CEC2006 benchmark functions.
 * The CEC2006 suite consists of 24 constrained optimization problems.
 * 
 * Usage: ./main <function_id> <dimension> <input_file>
 *   function_id: 1-24
 *   dimension: problem-specific (see problem definitions)
 *   input_file: text file with one value per line
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Function prototypes for all 24 CEC2006 problems */
void g01(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
void g02(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
void g03(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
void g04(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
void g05(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
void g06(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
void g07(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
void g08(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
void g09(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
void g10(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
void g11(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
void g12(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
void g13(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
void g14(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
void g15(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
void g16(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
void g17(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
void g18(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
void g19(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
void g20(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
void g21(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
void g22(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
void g23(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
void g24(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);

/* Problem dimensions and constraint counts */
typedef struct {
    int nx;  /* number of variables */
    int ng;  /* number of inequality constraints g(x) <= 0 */
    int nh;  /* number of equality constraints h(x) = 0 */
} ProblemInfo;

/* CEC2006 problem specifications */
static ProblemInfo problem_info[24] = {
    {13, 9, 0},   /* g01 */
    {20, 2, 0},   /* g02 - dimension is variable, using 20 as default */
    {10, 0, 1},   /* g03 - dimension is variable, using 10 as default */
    {5, 6, 0},    /* g04 */
    {4, 2, 3},    /* g05 */
    {2, 2, 0},    /* g06 */
    {10, 8, 0},   /* g07 */
    {2, 2, 0},    /* g08 */
    {7, 4, 0},    /* g09 */
    {8, 6, 0},    /* g10 */
    {2, 0, 1},    /* g11 */
    {3, 1, 0},    /* g12 */
    {5, 0, 3},    /* g13 */
    {10, 0, 3},   /* g14 */
    {3, 0, 2},    /* g15 */
    {5, 38, 0},   /* g16 */
    {6, 0, 4},    /* g17 */
    {9, 13, 0},   /* g18 */
    {15, 5, 0},   /* g19 */
    {24, 6, 14},  /* g20 */
    {7, 1, 5},    /* g21 */
    {22, 1, 19},  /* g22 */
    {9, 2, 4},    /* g23 */
    {2, 2, 0}     /* g24 */
};

/* Function pointer type */
typedef void (*BenchmarkFunction)(double *, double *, double *, double *, int, int, int, int);

/* Function pointer array */
static BenchmarkFunction functions[24] = {
    g01, g02, g03, g04, g05, g06, g07, g08,
    g09, g10, g11, g12, g13, g14, g15, g16,
    g17, g18, g19, g20, g21, g22, g23, g24
};

int main(int argc, char *argv[]) {
    int func_id, dimension, i;
    double *x, *f, *g, *h;
    FILE *input_file;
    char line[256];
    
    /* Check arguments */
    if (argc != 4) {
        printf("Usage: %s <function_id> <dimension> <input_file>\n", argv[0]);
        printf("  function_id: 1-24\n");
        printf("  dimension: problem dimension (use -1 for default)\n");
        printf("  input_file: text file with one value per line\n");
        return 1;
    }
    
    /* Parse arguments */
    func_id = atoi(argv[1]);
    dimension = atoi(argv[2]);
    
    if (func_id < 1 || func_id > 24) {
        fprintf(stderr, "Error: function_id must be between 1 and 24\n");
        return 1;
    }
    
    /* Get problem information */
    ProblemInfo info = problem_info[func_id - 1];
    
    /* Use default dimension if -1 specified */
    if (dimension == -1) {
        dimension = info.nx;
    }
    
    /* For problems g02 and g03, dimension can vary */
    if ((func_id == 2 || func_id == 3) && dimension > 0) {
        info.nx = dimension;
    } else if (dimension != info.nx) {
        fprintf(stderr, "Warning: Problem g%02d has fixed dimension %d, ignoring specified dimension %d\n",
                func_id, info.nx, dimension);
        dimension = info.nx;
    }
    
    /* Allocate memory */
    x = (double *)malloc(info.nx * sizeof(double));
    f = (double *)malloc(sizeof(double));
    g = (double *)malloc((info.ng > 0 ? info.ng : 1) * sizeof(double));
    h = (double *)malloc((info.nh > 0 ? info.nh : 1) * sizeof(double));
    
    if (!x || !f || !g || !h) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return 1;
    }
    
    /* Read input file */
    input_file = fopen(argv[3], "r");
    if (!input_file) {
        fprintf(stderr, "Error: Cannot open input file %s\n", argv[3]);
        free(x); free(f); free(g); free(h);
        return 1;
    }
    
    printf("Running function G%02d with %d variables\n", func_id, info.nx);
    
    for (i = 0; i < info.nx; i++) {
        if (fgets(line, sizeof(line), input_file) == NULL) {
            fprintf(stderr, "Error: Input file has fewer values than required (%d)\n", info.nx);
            fclose(input_file);
            free(x); free(f); free(g); free(h);
            return 1;
        }
        x[i] = atof(line);
        printf("x[%d] = %f\n", i + 1, x[i]);
    }
    fclose(input_file);
    
    /* Call the benchmark function */
    functions[func_id - 1](x, f, g, h, info.nx, 1, info.ng, info.nh);
    
    /* Print results */
    printf("\nObjective value = %.15E\n", f[0]);
    
    /* Print constraint violations if any */
    if (info.ng > 0) {
        printf("\nInequality constraints (g <= 0):\n");
        for (i = 0; i < info.ng; i++) {
            printf("g[%d] = %.15E", i + 1, g[i]);
            if (g[i] > 0) {
                printf(" (VIOLATED)");
            }
            printf("\n");
        }
    }
    
    if (info.nh > 0) {
        printf("\nEquality constraints (h = 0):\n");
        for (i = 0; i < info.nh; i++) {
            printf("h[%d] = %.15E", i + 1, h[i]);
            if (fabs(h[i]) > 1e-6) {
                printf(" (VIOLATED)");
            }
            printf("\n");
        }
    }
    
    /* Calculate total constraint violation */
    double total_violation = 0.0;
    for (i = 0; i < info.ng; i++) {
        if (g[i] > 0) {
            total_violation += g[i];
        }
    }
    for (i = 0; i < info.nh; i++) {
        total_violation += fabs(h[i]);
    }
    
    if (total_violation > 0) {
        printf("\nTotal constraint violation = %.15E\n", total_violation);
    } else {
        printf("\nAll constraints satisfied.\n");
    }
    
    printf("\nRoutine exited without any error.\n");
    
    /* Clean up */
    free(x);
    free(f);
    free(g);
    free(h);
    
    return 0;
}