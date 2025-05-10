/* Global variable and function definitions */

# ifndef _GLOBAL_H
# define _GLOBAL_H

# include <float.h>

/* Global Constants */
# define INF DBL_MAX
# define EPS 1.0e-10
# define E  2.7182818284590452353602874713526625
# define PI 3.1415926535897932384626433832795029

/* Global variables that you are required to initialize */
extern int nreal;                /* number of real variables */
extern int nfunc;                /* number of basic functions */
extern int function_id;          /* function identifier (1-25) */
extern long double bound;        /* required for plotting the function profiles for nreal=2 */
extern int density;              /* density of grid points for plotting for nreal=2 */

/* Global variables being used in evaluation of various functions */
/* These are initalized in file def2.c */
extern long double C;
extern long double global_bias;
extern long double *trans_x;
extern long double *basic_f;
extern long double *temp_x1;
extern long double *temp_x2;
extern long double *temp_x3;
extern long double *temp_x4;
extern long double *weight;
extern long double *sigma;
extern long double *lambda;
extern long double *bias;
extern long double *norm_x;
extern long double *norm_f;
extern long double **o;
extern long double **g;
extern long double ***l;

/* Function-specific global variables */
/* F5 */
extern long double **A_f5;
extern long double *B_f5;

/* F12 */
extern long double **A_f12;
extern long double **B_f12;
extern long double *alpha_f12;

/* Auxillary function declarations */
long double maximum (long double, long double);
long double minimum (long double, long double);
long double modulus (long double*, int);
long double dot (long double*, long double*, int);
long double mean (long double*, int);

/* Basic funcion declarations */
long double calc_ackley (long double*);
long double calc_rastrigin (long double*);
long double calc_weierstrass (long double*);
long double calc_griewank (long double*);
long double calc_sphere (long double*);
long double calc_schwefel (long double*);
long double calc_rosenbrock (long double *x);
long double nc_schaffer (long double, long double);
long double nc_rastrigin (long double*);

/* Utility function declarations */
void allocate_memory(void);
void initialize(void);
void transform (long double*, int);
void transform_norm (int);
void calc_weight (long double*);
void free_memory(void);

/* Function-specific initialization declarations */
void initialize_f1(void);
void initialize_f2(void);
void initialize_f3(void);
void initialize_f4(void);
void initialize_f5(void);
void initialize_f6(void);
void initialize_f7(void);
void initialize_f8(void);
void initialize_f9(void);
void initialize_f10(void);
void initialize_f11(void);
void initialize_f12(void);
void initialize_f13(void);
void initialize_f14(void);
void initialize_f15(void);
void initialize_f16(void);
void initialize_f17(void);
void initialize_f18(void);
void initialize_f19(void);
void initialize_f20(void);
void initialize_f21(void);
void initialize_f22(void);
void initialize_f23(void);
void initialize_f24(void);
void initialize_f25(void);

/* Function-specific calculation declarations */
long double calc_benchmark_f1(long double *x);
long double calc_benchmark_f2(long double *x);
long double calc_benchmark_f3(long double *x);
long double calc_benchmark_f4(long double *x);
long double calc_benchmark_f5(long double *x);
long double calc_benchmark_f6(long double *x);
long double calc_benchmark_f7(long double *x);
long double calc_benchmark_f8(long double *x);
long double calc_benchmark_f9(long double *x);
long double calc_benchmark_f10(long double *x);
long double calc_benchmark_f11(long double *x);
long double calc_benchmark_f12(long double *x);
long double calc_benchmark_f13(long double *x);
long double calc_benchmark_f14(long double *x);
long double calc_benchmark_f15(long double *x);
long double calc_benchmark_f16(long double *x);
long double calc_benchmark_f17(long double *x);
long double calc_benchmark_f18(long double *x);
long double calc_benchmark_f19(long double *x);
long double calc_benchmark_f20(long double *x);
long double calc_benchmark_f21(long double *x);
long double calc_benchmark_f22(long double *x);
long double calc_benchmark_f23(long double *x);
long double calc_benchmark_f24(long double *x);
long double calc_benchmark_f25(long double *x);

/* Normalization function declarations */
void calc_benchmark_norm_f15(void);
void calc_benchmark_norm_f16(void);
void calc_benchmark_norm_f17(void);
void calc_benchmark_norm_f18(void);
void calc_benchmark_norm_f19(void);
void calc_benchmark_norm_f20(void);
void calc_benchmark_norm_f21(void);
void calc_benchmark_norm_f22(void);
void calc_benchmark_norm_f23(void);
void calc_benchmark_norm_f24(void);
void calc_benchmark_norm_f25(void);

/* Benchmark function declaration */
long double calc_benchmark_func (long double*);
void calc_benchmark_norm(void);

# endif 
