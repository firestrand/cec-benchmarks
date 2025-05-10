# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "global.h"
# include "sub.h"
# include "rand.h"

/* Global variables that you are required to initialize */
int nreal;                  /* number of real variables */
int nfunc;                  /* number of basic functions */
int function_id;            /* function identifier (1-25) */
long double bound;          /* required for plotting the function profiles for nreal=2 */
int density;                /* density of grid points for plotting for nreal=2 */

/* Global variables being used in evaluation of various functions */
long double C;
long double global_bias;
long double *trans_x;
long double *basic_f;
long double *temp_x1;
long double *temp_x2;
long double *temp_x3;
long double *temp_x4;
long double *weight;
long double *sigma;
long double *lambda;
long double *bias;
long double *norm_x;
long double *norm_f;
long double **o;
long double **g;
long double ***l;

/* Function-specific global variables */
/* F5 */
long double **A_f5;
long double *B_f5;

/* F12 */
long double **A_f12;
long double **B_f12;
long double *alpha_f12; 
