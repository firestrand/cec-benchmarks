/* Source file for various benchmark functions */
/* Hard-coded for every function. */
/* Some redundancy is present here and there */
/* Refactored to use function-specific names instead of ifdefs */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "global.h"
# include "sub.h"
# include "rand.h"

/* Function to select the appropriate calculation function based on function_id */
long double calc_benchmark_func(long double *x)
{
    switch (function_id) {
        case 1: return calc_benchmark_f1(x);
        case 2: return calc_benchmark_f2(x);
        case 3: return calc_benchmark_f3(x);
        case 4: return calc_benchmark_f4(x);
        case 5: return calc_benchmark_f5(x);
        case 6: return calc_benchmark_f6(x);
        case 7: return calc_benchmark_f7(x);
        case 8: return calc_benchmark_f8(x);
        case 9: return calc_benchmark_f9(x);
        case 10: return calc_benchmark_f10(x);
        case 11: return calc_benchmark_f11(x);
        case 12: return calc_benchmark_f12(x);
        case 13: return calc_benchmark_f13(x);
        case 14: return calc_benchmark_f14(x);
        case 15: return calc_benchmark_f15(x);
        case 16: return calc_benchmark_f16(x);
        case 17: return calc_benchmark_f17(x);
        case 18: return calc_benchmark_f18(x);
        case 19: return calc_benchmark_f19(x);
        case 20: return calc_benchmark_f20(x);
        case 21: return calc_benchmark_f21(x);
        case 22: return calc_benchmark_f22(x);
        case 23: return calc_benchmark_f23(x);
        case 24: return calc_benchmark_f24(x);
        case 25: return calc_benchmark_f25(x);
        default:
            fprintf(stderr, "Error: Invalid function ID %d\n", function_id);
            exit(1);
            return 0.0; /* Never reached, just to silence warnings */
    }
}

/* Function to select the appropriate normalization function based on function_id */
void calc_benchmark_norm(void)
{
    switch (function_id) {
        case 15: calc_benchmark_norm_f15(); break;
        case 16: calc_benchmark_norm_f16(); break;
        case 17: calc_benchmark_norm_f17(); break;
        case 18: calc_benchmark_norm_f18(); break;
        case 19: calc_benchmark_norm_f19(); break;
        case 20: calc_benchmark_norm_f20(); break;
        case 21: calc_benchmark_norm_f21(); break;
        case 22: calc_benchmark_norm_f22(); break;
        case 23: calc_benchmark_norm_f23(); break;
        case 24: calc_benchmark_norm_f24(); break;
        case 25: calc_benchmark_norm_f25(); break;
        default:
            /* Functions 1-14 don't need normalization */
            if (function_id < 1 || function_id > 25) {
                fprintf(stderr, "Error: Invalid function ID %d for normalization\n", function_id);
                exit(1);
            }
            break;
    }
}

/* F1: Shifted Sphere Function */
long double calc_benchmark_f1(long double *x)
{
    long double res;
    transform(x, 0);
    basic_f[0] = calc_sphere(trans_x);
    res = basic_f[0] + bias[0];
    return (res);
}

/* F2: Shifted Schwefel's Problem 1.2 */
long double calc_benchmark_f2(long double *x)
{
    long double res;
    transform(x, 0);
    basic_f[0] = calc_schwefel(trans_x);
    res = basic_f[0] + bias[0];
    return (res);
}

/* F3: Shifted Rotated High Conditioned Elliptic Function */
long double calc_benchmark_f3(long double *x)
{
    int i;
    long double res;
    
    /* Write the x vector BEFORE transform for verification */
    {
        char filename[256];
        FILE *fp;
        int j;
        
        /* Create output directory */
        system("mkdir -p f3_data_dump");
        
        sprintf(filename, "f3_data_dump/x_before_transform_D%d.txt", nreal);
        fp = fopen(filename, "w");
        if (fp != NULL) {
            fprintf(fp, "# F3 Vector x before transform for D=%d\n", nreal);
            for (j=0; j<nreal; j++) {
                fprintf(fp, "%.15Lf\n", x[j]);
            }
            fclose(fp);
            printf("\nWrote x vector before transform to %s\n", filename);
        } else {
            printf("\nWarning: Could not write x vector to file\n");
        }
    }
    
    /* Now call transform */
    transform(x, 0);
    
    /* Write the x vector after transform for verification */
    {
        char filename[256];
        FILE *fp;
        int j;
        
        /* Create output directory */
        system("mkdir -p f3_data_dump");
        
        sprintf(filename, "f3_data_dump/x_after_transform_D%d.txt", nreal);
        fp = fopen(filename, "w");
        if (fp != NULL) {
            fprintf(fp, "# F3 Vector x after transform for D=%d\n", nreal);
            for (j=0; j<nreal; j++) {
                fprintf(fp, "%.15Lf\n", x[j]);
            }
            fclose(fp);
            printf("\nWrote x vector after transform to %s\n", filename);
        } else {
            printf("\nWarning: Could not write x vector to file\n");
        }

        /* Also write trans_x vector for completeness */
        sprintf(filename, "f3_data_dump/trans_x_D%d.txt", nreal);
        fp = fopen(filename, "w");
        if (fp != NULL) {
            fprintf(fp, "# F3 trans_x vector for D=%d\n", nreal);
            for (j=0; j<nreal; j++) {
                fprintf(fp, "%.15Lf\n", trans_x[j]);
            }
            fclose(fp);
        }
    }

    basic_f[0] = 0.0;
    for (i=0; i<nreal; i++)
    {
        basic_f[0] += trans_x[i]*trans_x[i]*pow(1.0e6,i/(nreal-1.0));
    }
    res = basic_f[0] + bias[0];
    return (res);
}

/* F4: Shifted Schwefel's Problem 1.2 with Noise in Fitness */
long double calc_benchmark_f4(long double *x)
{
    long double res;
    transform(x, 0);
    basic_f[0] = calc_schwefel(trans_x)*(1.0 + 0.4*fabs(randomnormaldeviate()));
    res = basic_f[0] + bias[0];
    return (res);
}

/* F5: Schwefel's Problem 2.6 with Global Optimum on Bounds */
long double calc_benchmark_f5(long double *x)
{
    int i, j;
    long double res;
    basic_f[0] = -INF;
    for (i=0; i<nreal; i++)
    {
        res=0.0;
        for (j=0; j<nreal; j++)
        {
            res += A_f5[i][j]*x[j];
        }
        res = fabs(res-B_f5[i]);
        if (basic_f[0] < res)
        {
            basic_f[0] = res;
        }
    }
    res = basic_f[0] + bias[0];
    return (res);
}

/* F6: Shifted Rosenbrock's Function */
long double calc_benchmark_f6(long double *x)
{
    long double res;
    transform(x, 0);
    basic_f[0] = calc_rosenbrock(trans_x);
    res = basic_f[0] + bias[0];
    return (res);
}

/* F7: Shifted Rotated Griewank's Function */
long double calc_benchmark_f7(long double *x)
{
    long double res;
    transform(x, 0);
    basic_f[0] = calc_griewank(trans_x);
    res = basic_f[0] + bias[0];
    return (res);
}

/* F8: Shifted Rotated Ackley's Function with Global Optimum on Bounds */
long double calc_benchmark_f8(long double *x)
{
    long double res;
    transform(x, 0);
    basic_f[0] = calc_ackley(trans_x);
    res = basic_f[0] + bias[0];
    return (res);
}

/* F9: Shifted Rastrigin's Function */
long double calc_benchmark_f9(long double *x)
{
    long double res;
    transform(x, 0);
    basic_f[0] = calc_rastrigin(trans_x);
    res = basic_f[0] + bias[0];
    return (res);
}

/* F10: Shifted Rotated Rastrigin's Function */
long double calc_benchmark_f10(long double *x)
{
    long double res;
    transform(x, 0);
    basic_f[0] = calc_rastrigin(trans_x);
    res = basic_f[0] + bias[0];
    return (res);
}

/* F11: Shifted Rotated Weierstrass Function */
long double calc_benchmark_f11(long double *x)
{
    int i;
    long double res;
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform(x, 0);
    basic_f[0] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    res = basic_f[0] + bias[0];
    return (res);
}

/* F12: Schwefel's Problem 2.13 */
long double calc_benchmark_f12(long double *x)
{
    long double res;
    long double sum1, sum2;
    int i, j;
    basic_f[0] = 0.0;
    for (i=0; i<nreal; i++)
    {
        sum1 = 0.0;
        sum2 = 0.0;
        for (j=0; j<nreal; j++)
        {
            sum1 += A_f12[i][j]*sin(alpha_f12[j]) + B_f12[i][j]*cos(alpha_f12[j]);
            sum2 += A_f12[i][j]*sin(x[j]) + B_f12[i][j]*cos(x[j]);
        }
        basic_f[0] += pow((sum1-sum2),2.0);
    }
    res = basic_f[0] + bias[0];
    return (res);
}

/* F13: Shifted Expanded Griewank's plus Rosenbrock's Function */
long double calc_benchmark_f13(long double *x)
{
    int i;
    long double temp;
    long double res;
    transform(x, 0);
    res = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        res += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    res += (temp*temp)/4000.0 - cos(temp) + 1.0 + bias[0];
    return (res);
}

/* F14: Shifted Rotated Expanded Scaffer's F6 Function */
long double calc_benchmark_f14(long double *x)
{
    int i;
    long double temp1, temp2;
    long double res;
    transform(x,0);
    res = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        res += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    res += 0.5 + (temp1-0.5)/(pow(temp2,2.0)) + bias[0];
    return (res);
}

void calc_benchmark_norm_f15(void)
{
    int i;
    transform_norm (0);    norm_f[0] = calc_rastrigin(trans_x);
    transform_norm (1);    norm_f[1] = calc_rastrigin(trans_x);
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform_norm (2);    norm_f[2] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (3);    norm_f[3] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (4);    norm_f[4] = calc_griewank(trans_x);
    transform_norm (5);    norm_f[5] = calc_griewank(trans_x);
    transform_norm (6);    norm_f[6] = calc_ackley(trans_x);
    transform_norm (7);    norm_f[7] = calc_ackley(trans_x);
    transform_norm (8);    norm_f[8] = calc_sphere(trans_x);
    transform_norm (9);    norm_f[9] = calc_sphere(trans_x);
    return;
}

long double calc_benchmark_f15(long double *x) 
{
    int i;
    long double res; 
    transform (x, 0);    basic_f[0] = calc_rastrigin(trans_x);
    transform (x, 1);    basic_f[1] = calc_rastrigin(trans_x);
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform (x, 2);    basic_f[2] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 3);    basic_f[3] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 4);    basic_f[4] = calc_griewank(trans_x);
    transform (x, 5);    basic_f[5] = calc_griewank(trans_x);
    transform (x, 6);    basic_f[6] = calc_ackley(trans_x);
    transform (x, 7);    basic_f[7] = calc_ackley(trans_x);
    transform (x, 8);    basic_f[8] = calc_sphere(trans_x);
    transform (x, 9);    basic_f[9] = calc_sphere(trans_x);
    for (i=0; i<nfunc; i++)
    {
        basic_f[i] *= C/norm_f[i];
    }
    calc_weight(x);
    res = global_bias;
    for (i=0; i<nfunc; i++)
    {
        res += weight[i]*(basic_f[i]+bias[i]);
    }
    return (res);
}

void calc_benchmark_norm_f16()
{
    int i;
    transform_norm (0);    norm_f[0] = calc_rastrigin(trans_x);
    transform_norm (1);    norm_f[1] = calc_rastrigin(trans_x);
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform_norm (2);    norm_f[2] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (3);    norm_f[3] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (4);    norm_f[4] = calc_griewank(trans_x);
    transform_norm (5);    norm_f[5] = calc_griewank(trans_x);
    transform_norm (6);    norm_f[6] = calc_ackley(trans_x);
    transform_norm (7);    norm_f[7] = calc_ackley(trans_x);
    transform_norm (8);    norm_f[8] = calc_sphere(trans_x);
    transform_norm (9);    norm_f[9] = calc_sphere(trans_x);
    return;
}

long double calc_benchmark_f16(long double *x)
{
    int i;
    long double res;
    transform (x, 0);    basic_f[0] = calc_rastrigin(trans_x);
    transform (x, 1);    basic_f[1] = calc_rastrigin(trans_x);
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform (x, 2);    basic_f[2] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 3);    basic_f[3] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 4);    basic_f[4] = calc_griewank(trans_x);
    transform (x, 5);    basic_f[5] = calc_griewank(trans_x);
    transform (x, 6);    basic_f[6] = calc_ackley(trans_x);
    transform (x, 7);    basic_f[7] = calc_ackley(trans_x);
    transform (x, 8);    basic_f[8] = calc_sphere(trans_x);
    transform (x, 9);    basic_f[9] = calc_sphere(trans_x);
    for (i=0; i<nfunc; i++)
    {
        basic_f[i] *= C/norm_f[i];
    }
    calc_weight(x);
    res = global_bias;
    for (i=0; i<nfunc; i++)
    {
        res += weight[i]*(basic_f[i]+bias[i]);
    }
    return (res);
}

void calc_benchmark_norm_f17(void)
{
    int i;
    transform_norm (0);    norm_f[0] = calc_rastrigin(trans_x);
    transform_norm (1);    norm_f[1] = calc_rastrigin(trans_x);
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform_norm (2);    norm_f[2] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (3);    norm_f[3] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (4);    norm_f[4] = calc_griewank(trans_x);
    transform_norm (5);    norm_f[5] = calc_griewank(trans_x);
    transform_norm (6);    norm_f[6] = calc_ackley(trans_x);
    transform_norm (7);    norm_f[7] = calc_ackley(trans_x);
    transform_norm (8);    norm_f[8] = calc_sphere(trans_x);
    transform_norm (9);    norm_f[9] = calc_sphere(trans_x);
    return;
}

long double calc_benchmark_f17(long double *x)
{
    int i;
    long double res;
    transform (x, 0);    basic_f[0] = calc_rastrigin(trans_x);
    transform (x, 1);    basic_f[1] = calc_rastrigin(trans_x);
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform (x, 2);    basic_f[2] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 3);    basic_f[3] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 4);    basic_f[4] = calc_griewank(trans_x);
    transform (x, 5);    basic_f[5] = calc_griewank(trans_x);
    transform (x, 6);    basic_f[6] = calc_ackley(trans_x);
    transform (x, 7);    basic_f[7] = calc_ackley(trans_x);
    transform (x, 8);    basic_f[8] = calc_sphere(trans_x);
    transform (x, 9);    basic_f[9] = calc_sphere(trans_x);
    for (i=0; i<nfunc; i++)
    {
        basic_f[i] *= C/norm_f[i];
    }
    calc_weight(x);
    res = 0.0;
    for (i=0; i<nfunc; i++)
    {
        res += weight[i]*(basic_f[i]+bias[i]);
    }
    res = res*(1.0 + 0.2*fabs(randomnormaldeviate())) + global_bias;
    return (res);
}

void calc_benchmark_norm_f18(void)
{
    int i;
    transform_norm (0);    norm_f[0] = calc_ackley(trans_x);
    transform_norm (1);    norm_f[1] = calc_ackley(trans_x);
    transform_norm (2);    norm_f[2] = calc_rastrigin(trans_x);
    transform_norm (3);    norm_f[3] = calc_rastrigin(trans_x);
    transform_norm (4);    norm_f[4] = calc_sphere(trans_x);
    transform_norm (5);    norm_f[5] = calc_sphere(trans_x);
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform_norm (6);    norm_f[6] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (7);    norm_f[7] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (8);    norm_f[8] = calc_griewank(trans_x);
    transform_norm (9);    norm_f[9] = calc_griewank(trans_x);
    return;
}

long double calc_benchmark_f18(long double *x)
{
    int i;
    long double res;
    transform (x, 0);    basic_f[0] = calc_ackley(trans_x);
    transform (x, 1);    basic_f[1] = calc_ackley(trans_x);
    transform (x, 2);    basic_f[2] = calc_rastrigin(trans_x);
    transform (x, 3);    basic_f[3] = calc_rastrigin(trans_x);
    transform (x, 4);    basic_f[4] = calc_sphere(trans_x);
    transform (x, 5);    basic_f[5] = calc_sphere(trans_x);
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform (x, 6);    basic_f[6] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 7);    basic_f[7] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 8);    basic_f[8] = calc_griewank(trans_x);
    transform (x, 9);    basic_f[9] = calc_griewank(trans_x);
    for (i=0; i<nfunc; i++)
    {
        basic_f[i] *= C/norm_f[i];
    }
    calc_weight(x);
    res = global_bias;
    for (i=0; i<nfunc; i++)
    {
        res += weight[i]*(basic_f[i]+bias[i]);
    }
    return (res);
}

void calc_benchmark_norm_f19(void)
{
    int i;
    transform_norm (0);    norm_f[0] = calc_ackley(trans_x);
    transform_norm (1);    norm_f[1] = calc_ackley(trans_x);
    transform_norm (2);    norm_f[2] = calc_rastrigin(trans_x);
    transform_norm (3);    norm_f[3] = calc_rastrigin(trans_x);
    transform_norm (4);    norm_f[4] = calc_sphere(trans_x);
    transform_norm (5);    norm_f[5] = calc_sphere(trans_x);
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform_norm (6);    norm_f[6] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (7);    norm_f[7] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (8);    norm_f[8] = calc_griewank(trans_x);
    transform_norm (9);    norm_f[9] = calc_griewank(trans_x);
    return;
}

long double calc_benchmark_f19(long double *x)
{
    int i;
    long double res;
    transform (x, 0);    basic_f[0] = calc_ackley(trans_x);
    transform (x, 1);    basic_f[1] = calc_ackley(trans_x);
    transform (x, 2);    basic_f[2] = calc_rastrigin(trans_x);
    transform (x, 3);    basic_f[3] = calc_rastrigin(trans_x);
    transform (x, 4);    basic_f[4] = calc_sphere(trans_x);
    transform (x, 5);    basic_f[5] = calc_sphere(trans_x);
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform (x, 6);    basic_f[6] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 7);    basic_f[7] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 8);    basic_f[8] = calc_griewank(trans_x);
    transform (x, 9);    basic_f[9] = calc_griewank(trans_x);
    for (i=0; i<nfunc; i++)
    {
        basic_f[i] *= C/norm_f[i];
    }
    calc_weight(x);
    res = global_bias;
    for (i=0; i<nfunc; i++)
    {
        res += weight[i]*(basic_f[i]+bias[i]);
    }
    return (res);
}

void calc_benchmark_norm_f20(void)
{
    int i;
    transform_norm (0);    norm_f[0] = calc_ackley(trans_x);
    transform_norm (1);    norm_f[1] = calc_ackley(trans_x);
    transform_norm (2);    norm_f[2] = calc_rastrigin(trans_x);
    transform_norm (3);    norm_f[3] = calc_rastrigin(trans_x);
    transform_norm (4);    norm_f[4] = calc_sphere(trans_x);
    transform_norm (5);    norm_f[5] = calc_sphere(trans_x);
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform_norm (6);    norm_f[6] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (7);    norm_f[7] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (8);    norm_f[8] = calc_griewank(trans_x);
    transform_norm (9);    norm_f[9] = calc_griewank(trans_x);
    return;
}

long double calc_benchmark_f20(long double *x)
{
    int i;
    long double res;
    transform (x, 0);    basic_f[0] = calc_ackley(trans_x);
    transform (x, 1);    basic_f[1] = calc_ackley(trans_x);
    transform (x, 2);    basic_f[2] = calc_rastrigin(trans_x);
    transform (x, 3);    basic_f[3] = calc_rastrigin(trans_x);
    transform (x, 4);    basic_f[4] = calc_sphere(trans_x);
    transform (x, 5);    basic_f[5] = calc_sphere(trans_x);
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform (x, 6);    basic_f[6] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 7);    basic_f[7] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 8);    basic_f[8] = calc_griewank(trans_x);
    transform (x, 9);    basic_f[9] = calc_griewank(trans_x);
    for (i=0; i<nfunc; i++)
    {
        basic_f[i] *= C/norm_f[i];
    }
    calc_weight(x);
    res = global_bias;
    for (i=0; i<nfunc; i++)
    {
        res += weight[i]*(basic_f[i]+bias[i]);
    }
    return (res);
}

void calc_benchmark_norm_f21(void)
{
    int i;
    long double temp1, temp2, temp;
    transform_norm (0);
    norm_f[0] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        norm_f[0] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    norm_f[0] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform_norm (1);
    norm_f[1] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        norm_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    norm_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform_norm (2);    norm_f[2] = calc_rastrigin(trans_x);
    transform_norm (3);    norm_f[3] = calc_rastrigin(trans_x);
    transform_norm(4);
    norm_f[4] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        norm_f[4] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    norm_f[4] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    transform_norm(5);
    norm_f[5] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        norm_f[5] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    norm_f[5] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform_norm (6);    norm_f[6] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (7);    norm_f[7] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (8);    norm_f[8] = calc_griewank(trans_x);
    transform_norm (9);    norm_f[9] = calc_griewank(trans_x);
    return;
}

long double calc_benchmark_f21(long double *x)
{
    int i;
    long double temp1, temp2, temp;
    long double res;
    transform (x, 0);
    basic_f[0] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        basic_f[0] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    basic_f[0] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform (x, 1);
    basic_f[1] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        basic_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    basic_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform (x, 2);    basic_f[2] = calc_rastrigin(trans_x);
    transform (x, 3);    basic_f[3] = calc_rastrigin(trans_x);
    transform (x, 4);
    basic_f[4] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        basic_f[4] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    basic_f[4] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    transform(x, 5);
    basic_f[5] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        basic_f[5] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    basic_f[5] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform (x, 6);    basic_f[6] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 7);    basic_f[7] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 8);    basic_f[8] = calc_griewank(trans_x);
    transform (x, 9);    basic_f[9] = calc_griewank(trans_x);
    for (i=0; i<nfunc; i++)
    {
        basic_f[i] *= C/norm_f[i];
    }
    calc_weight(x);
    res = global_bias;
    for (i=0; i<nfunc; i++)
    {
        res += weight[i]*(basic_f[i]+bias[i]);
    }
    return (res);
}

void calc_benchmark_norm_f22(void)
{
    int i;
    long double temp1, temp2, temp;
    transform_norm (0);
    norm_f[0] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        norm_f[0] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    norm_f[0] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform_norm (1);
    norm_f[1] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        norm_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    norm_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform_norm (2);    norm_f[2] = calc_rastrigin(trans_x);
    transform_norm (3);    norm_f[3] = calc_rastrigin(trans_x);
    transform_norm(4);
    norm_f[4] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        norm_f[4] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    norm_f[4] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    transform_norm(5);
    norm_f[5] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        norm_f[5] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    norm_f[5] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform_norm (6);    norm_f[6] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (7);    norm_f[7] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (8);    norm_f[8] = calc_griewank(trans_x);
    transform_norm (9);    norm_f[9] = calc_griewank(trans_x);
    return;
}

long double calc_benchmark_f22(long double *x)
{
    int i;
    long double temp1, temp2, temp;
    long double res;
    transform (x, 0);
    basic_f[0] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        basic_f[0] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    basic_f[0] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform (x, 1);
    basic_f[1] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        basic_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    basic_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform (x, 2);    basic_f[2] = calc_rastrigin(trans_x);
    transform (x, 3);    basic_f[3] = calc_rastrigin(trans_x);
    transform (x, 4);
    basic_f[4] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        basic_f[4] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    basic_f[4] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    transform(x, 5);
    basic_f[5] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        basic_f[5] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    basic_f[5] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform (x, 6);    basic_f[6] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 7);    basic_f[7] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 8);    basic_f[8] = calc_griewank(trans_x);
    transform (x, 9);    basic_f[9] = calc_griewank(trans_x);
    for (i=0; i<nfunc; i++)
    {
        basic_f[i] *= C/norm_f[i];
    }
    calc_weight(x);
    res = global_bias;
    for (i=0; i<nfunc; i++)
    {
        res += weight[i]*(basic_f[i]+bias[i]);
    }
    return (res);
}

void calc_benchmark_norm_f23(void)
{
    int i;
    long double temp1, temp2, temp;
    transform_norm (0);
    norm_f[0] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        norm_f[0] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    norm_f[0] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform_norm (1);
    norm_f[1] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        norm_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    norm_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform_norm (2);    norm_f[2] = calc_rastrigin(trans_x);
    transform_norm (3);    norm_f[3] = calc_rastrigin(trans_x);
    transform_norm(4);
    norm_f[4] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        norm_f[4] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    norm_f[4] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    transform_norm(5);
    norm_f[5] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        norm_f[5] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    norm_f[5] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform_norm (6);    norm_f[6] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (7);    norm_f[7] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (8);    norm_f[8] = calc_griewank(trans_x);
    transform_norm (9);    norm_f[9] = calc_griewank(trans_x);
    return;
}

long double calc_benchmark_f23(long double *x)
{
    int i;
    long double temp1, temp2, temp;
    long double res;
    int a;
    long double b;
    for (i=0; i<nreal; i++)
    {
        if (fabs(x[i]-o[0][i]) >= 0.5)
        {
            res = 2.0*x[i];
            a = res;
            b = fabs(res-a);
            if (b<0.5)
            {
                temp_x4[i] = a/2.0;
            }
            else
            {
                if (res<=0.0)
                {
                    temp_x4[i] = (a-1.0)/2.0;
                }
                else
                {
                    temp_x4[i] = (a+1.0)/2.0;
                }
            }
        }
        else
        {
            temp_x4[i] = x[i];
        }
    }
    transform (temp_x4, 0);
    basic_f[0] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        basic_f[0] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    basic_f[0] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform (temp_x4, 1);
    basic_f[1] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        basic_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    basic_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform (temp_x4, 2);    basic_f[2] = calc_rastrigin(trans_x);
    transform (temp_x4, 3);    basic_f[3] = calc_rastrigin(trans_x);
    transform (temp_x4, 4);
    basic_f[4] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        basic_f[4] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    basic_f[4] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    transform(temp_x4, 5);
    basic_f[5] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        basic_f[5] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    basic_f[5] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform (temp_x4, 6);    basic_f[6] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (temp_x4, 7);    basic_f[7] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (temp_x4, 8);    basic_f[8] = calc_griewank(trans_x);
    transform (temp_x4, 9);    basic_f[9] = calc_griewank(trans_x);
    for (i=0; i<nfunc; i++)
    {
        basic_f[i] *= C/norm_f[i];
    }
    calc_weight(temp_x4);
    res = global_bias;
    for (i=0; i<nfunc; i++)
    {
        res += weight[i]*(basic_f[i]+bias[i]);
    }
    return (res);
}

void calc_benchmark_norm_f24(void)
{
    int i;
    long double temp1, temp2, temp;
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform_norm (0);    norm_f[0] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (1);
    norm_f[1] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        norm_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    norm_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform_norm (2);
    norm_f[2] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        norm_f[2] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    norm_f[2] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    transform_norm (3);    norm_f[3] = calc_ackley(trans_x);
    transform_norm (4);    norm_f[4] = calc_rastrigin(trans_x);
    transform_norm (5);    norm_f[5] = calc_griewank(trans_x);
    transform_norm (6);
    norm_f[6] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        norm_f[6] += nc_schaffer(trans_x[i], trans_x[i+1]);
    }
    norm_f[6] += nc_schaffer(trans_x[nreal-1], trans_x[0]);
    transform_norm(7);    norm_f[7] = nc_rastrigin(trans_x);
    transform_norm (8);
    norm_f[8] = 0.0;
    for (i=0; i<nreal; i++)
    {
        norm_f[8] += trans_x[i]*trans_x[i]*pow(1.0e6,i/(nreal-1.0));
    }
    transform_norm (9);    norm_f[9] = calc_sphere(trans_x)*(1.0 + 0.1*fabs(randomnormaldeviate()));
    return;
}

long double calc_benchmark_f24(long double *x)
{
    int i;
    long double temp1, temp2, temp;
    long double res;
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    /* First function */
    transform (x, 0);    basic_f[0] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);

    /* Second function */
    transform (x, 1);
    basic_f[1] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        basic_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    basic_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));

    /* Third Function */
    transform (x, 2);
    basic_f[2] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        basic_f[2] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    basic_f[2] += (temp*temp)/4000.0 - cos(temp) + 1.0;

    transform (x, 3);    basic_f[3] = calc_ackley(trans_x);
    transform (x, 4);    basic_f[4] = calc_rastrigin(trans_x);
    transform (x, 5);    basic_f[5] = calc_griewank(trans_x);

    /* Seventh Function */
    transform (x, 6);
    basic_f[6] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        basic_f[6] += nc_schaffer(trans_x[i], trans_x[i+1]);
    }
    basic_f[6] += nc_schaffer(trans_x[nreal-1], trans_x[0]);

    transform (x, 7);    basic_f[7] = nc_rastrigin(trans_x);

    transform (x, 8);
    basic_f[8] = 0.0;
    for (i=0; i<nreal; i++)
    {
        basic_f[8] += trans_x[i]*trans_x[i]*pow(1.0e6,i/(nreal-1.0));
    }
    transform (x, 9);    basic_f[9] = (calc_sphere(trans_x))*(1.0 + 0.1*fabs(randomnormaldeviate()));
    for (i=0; i<nfunc; i++)
    {
        basic_f[i] *= C/norm_f[i];
    }
    calc_weight(x);
    res = global_bias;
    for (i=0; i<nfunc; i++)
    {
        res += weight[i]*(basic_f[i]+bias[i]);
    }
    return (res);
}

long double calc_benchmark_f25(long double *x) { return calc_benchmark_f24(x); }
void calc_benchmark_norm_f25(void) { calc_benchmark_norm_f24(); }
