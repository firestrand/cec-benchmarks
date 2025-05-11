/* Source file for custom initialization */
/* Hard-coded for every function based on the type and nature of input files */
/* At present hard-coded for D=2, 10, 30 and 50 */
/* Refactored to use function-specific names instead of ifdefs */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "global.h"
# include "sub.h"
# include "rand.h"

/* Function to select the appropriate initialization function based on function_id */
void initialize(void)
{
    switch (function_id) {
        case 1: initialize_f1(); break;
        case 2: initialize_f2(); break;
        case 3: initialize_f3(); break;
        case 4: initialize_f4(); break;
        case 5: initialize_f5(); break;
        case 6: initialize_f6(); break;
        case 7: initialize_f7(); break;
        case 8: initialize_f8(); break;
        case 9: initialize_f9(); break;
        case 10: initialize_f10(); break;
        case 11: initialize_f11(); break;
        case 12: initialize_f12(); break;
        case 13: initialize_f13(); break;
        case 14: initialize_f14(); break;
        case 15: initialize_f15(); break;
        case 16: initialize_f16(); break;
        case 17: initialize_f17(); break;
        case 18: initialize_f18(); break;
        case 19: initialize_f19(); break;
        case 20: initialize_f20(); break;
        case 21: initialize_f21(); break;
        case 22: initialize_f22(); break;
        case 23: initialize_f23(); break;
        case 24: initialize_f24(); break;
        case 25: initialize_f25(); break;
        default:
            fprintf(stderr, "Error: Invalid function ID %d\n", function_id);
            exit(1);
    }
}

/* F1: Shifted Sphere Function */
void initialize_f1(void)
{
    int i, j;
    FILE *fpt;
    fpt = fopen("input_data/f01/shift_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file input_data/f01/shift_D50.txt for reading \n");
        exit(0);
    }
    
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
        }
    }
    fclose(fpt);
    bias[0] = -450.0;
    return;
}

/* F2: Shifted Schwefel's Problem 1.2 */
void initialize_f2(void)
{
    int i, j;
    FILE *fpt;
    fpt = fopen("input_data/f02/shift_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file input_data/f02/shift_D50.txt for reading \n");
        exit(0);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
        }
    }
    fclose(fpt);
    bias[0] = -450.0;
    return;
}

/* F3: Shifted Rotated High Conditioned Elliptic Function */
void initialize_f3(void)
{
    int i, j;
    FILE *fpt;
    if (nreal==2) fpt = fopen("input_data/f03/rot_D2.txt","r");
    if (nreal==10) fpt = fopen("input_data/f03/rot_D10.txt","r");
    if (nreal==30) fpt = fopen("input_data/f03/rot_D30.txt","r");
    if (nreal==50) fpt = fopen("input_data/f03/rot_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open rotation matrix file elliptic_M_D*.txt for reading \n");
        exit(0);
    }
    for (i=0; i<nreal; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&g[i][j]);
        }
    }
    fclose(fpt);
    fpt = fopen("input_data/f03/shift_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open shift vector file input_data/f03/shift_D50.txt for reading \n");
        exit(0);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
        }
    }
    fclose(fpt);
    bias[0] = -450.0;
    return;
}

/* F4: Shifted Schwefel's Problem 1.2 with Noise in Fitness */
void initialize_f4(void)
{
    int i, j;
    FILE *fpt;
    fpt = fopen("input_data/f02/shift_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file input_data/f02/shift_D50.txt for reading \n");
        exit(0);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
        }
    }
    fclose(fpt);
    bias[0] = -450.0;
    return;
}

/* F5: Schwefel's Problem 2.6 with Global Optimum on Bounds */
void initialize_f5(void)
{
    int i, j;
    int index;
    FILE *fpt;
    
    /* Allocate memory for F5 specific arrays */
    A_f5 = (long double **)malloc(nreal*sizeof(long double*));
    for (i=0; i<nreal; i++)
    {
        A_f5[i] = (long double *)malloc(nreal*sizeof(long double));
    }
    B_f5 = (long double *)malloc(nreal*sizeof(long double));

    fpt = fopen("input_data/f05/shift_D50.txt","r");
    if (fpt==NULL) {
        fprintf(stderr,"\n Error: Cannot open input file for reading \n");
        exit(0);
    }
    
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
        }
    }
    for (i=0; i<nreal; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&A_f5[i][j]);
        }
    }
    fclose(fpt);
    if (nreal%4==0)
    {
        index = nreal/4;
    }
    else
    {
        index = nreal/4 + 1;
    }
    for (i=0; i<index; i++)
    {
        o[0][i] = -100.0;
    }
    index = (3*nreal)/4 - 1;
    for (i=index; i<nreal; i++)
    {
        o[0][i] = 100.0;
    }
    for (i=0; i<nreal; i++)
    {
        B_f5[i] = 0.0;
        for (j=0; j<nreal; j++)
        {
            B_f5[i] += A_f5[i][j]*o[0][j];
        }
    }
    bias[0] = -310.0;
    return;
}

/* F6: Shifted Rosenbrock's Function */
void initialize_f6(void)
{
    int i, j;
    FILE *fpt;
    fpt = fopen("input_data/f06/shift_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file for reading \n");
        exit(0);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
            o[i][j] -= 1.0;
        }
    }
    fclose(fpt);
    bias[0] = 390.0;
    return;
}

/* F7: Shifted Rotated Griewank's Function */
void initialize_f7(void)
{
    int i, j;
    FILE *fpt;
    if (nreal==2)    fpt = fopen("input_data/f07/rot_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/f07/rot_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/f07/rot_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/f07/rot_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file for reading \n");
        exit(0);
    }
    for (i=0; i<nreal; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&g[i][j]);
        }
    }
    fclose(fpt);
    fpt = fopen("input_data/f07/shift_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file for reading \n");
        exit(0);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
        }
    }
    fclose(fpt);
    bias[0] = -180.0;
    return;
}

/* F8: Shifted Rotated Ackley's Function with Global Optimum on Bounds */
void initialize_f8(void)
{
    int i, j;
    int index;
    FILE *fpt;
    if (nreal==2)    fpt = fopen("input_data/f08/rot_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/f08/rot_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/f08/rot_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/f08/rot_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file for reading \n");
        exit(0);
    }
    for (i=0; i<nreal; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&g[i][j]);
        }
    }
    fclose(fpt);
    fpt = fopen("input_data/f08/shift_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file for reading \n");
        exit(0);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
        }
    }
    fclose(fpt);
    index = nreal/2;
    for (i=1; i<=index; i++)
    {
        o[0][2*i-2] = -32.0;
    }
    bias[0] = -140.0;
    return;
}

/* F9: Shifted Rastrigin's Function */
void initialize_f9(void)
{
    int i, j;
    FILE *fpt;
    fpt = fopen("input_data/f09/shift_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file for reading \n");
        exit(0);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
        }
    }
    fclose(fpt);
    bias[0] = -330.0;
    return;
}

/* F10: Shifted Rotated Rastrigin's Function */
void initialize_f10(void)
{
    int i, j;
    FILE *fpt;
    if (nreal==2)    fpt = fopen("input_data/f10/rot_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/f10/rot_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/f10/rot_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/f10/rot_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file for reading \n");
        exit(0);
    }
    for (i=0; i<nreal; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&g[i][j]);
        }
    }
    fclose(fpt);
    /* The shift is the same as f9 */
    fpt = fopen("input_data/f09/shift_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file for reading \n");
        exit(0);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
        }
    }
    fclose(fpt);
    bias[0] = -330.0;
    return;
}

/* F11: Shifted Rotated Weierstrass Function */
void initialize_f11(void)
{
    int i, j;
    FILE *fpt;
    if (nreal==2)    fpt = fopen("input_data/f11/rot_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/f11/rot_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/f11/rot_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/f11/rot_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file weierstrass_M_D*.txt for reading \n");
        exit(0);
    }
    for (i=0; i<nreal; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&g[i][j]);
        }
    }
    fclose(fpt);
    fpt = fopen("input_data/f11/shift_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file input_data/f11/shift_D50.txt for reading \n");
        exit(0);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
        }
    }
    fclose(fpt);
    bias[0] = 90.0;
    return;
}

/* F12: Schwefel's Problem 2.13 */
void initialize_f12(void)
{
    int i, j;
    FILE *fpt;
    
    /* Allocate memory for F12 specific arrays */
    A_f12 = (long double **)malloc(nreal*sizeof(long double*));
    B_f12 = (long double **)malloc(nreal*sizeof(long double*));
    alpha_f12 = (long double *)malloc(nreal*sizeof(long double));
    
    for (i=0; i<nreal; i++)
    {
        A_f12[i] = (long double *)malloc(nreal*sizeof(long double));
        B_f12[i] = (long double *)malloc(nreal*sizeof(long double));
    }
    fpt = fopen("input_data/f12/bias_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file for function 12 \n");
        exit(0);
    }
    
    /* Read alpha values */
    for (i=0; i<nreal; i++)
    {
        fscanf(fpt,"%Lf",&alpha_f12[i]);
    }
    
    /* Read A values */
    for (i=0; i<nreal; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&A_f12[i][j]);
        }
    }
    
    /* Read B values */
    for (i=0; i<nreal; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&B_f12[i][j]);
        }
    }
    if (i!=100)
    {
        for (i=nreal; i<100; i++)
        {
            /* Skip remaining lines */
        }
    }
    /* Reading alpha */
    for (i=0; i<nreal; i++)
    {
        fscanf(fpt,"%Lf",&alpha_f12[i]);
    }
    fclose(fpt);
    bias[0] = -460.0;
    return;
}

void initialize_f13(void) 
{
    int i, j;
    FILE *fpt;
    fpt = fopen("input_data/f13/shift_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file for reading \n");
        exit(0);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
            o[i][j] -= 1.0;
        }
    }
    fclose(fpt);
    bias[0] = -130.0;
    return;
}
void initialize_f14(void) 
{
    int i, j;
    FILE *fpt;
    if (nreal==2)    fpt = fopen("input_data/f14/rot_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/f14/rot_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/f14/rot_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/f14/rot_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file for reading \n");
        exit(0);
    }
    for (i=0; i<nreal; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&g[i][j]);
        }
    }
    fclose(fpt);
    fpt = fopen("input_data/f14/shift_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file for reading \n");
        exit(0);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
        }
    }
    fclose(fpt);
    bias[0] = -300.0;
    return;
}
void initialize_f15(void) 
{
    int i, j;
    FILE *fpt;
    
    printf("\nDEBUG: Starting initialize_f15\n");
    
    fpt = fopen("input_data/f15/shift_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file input_data/f15/shift_D50.txt for reading \n");
        exit(0);
    }
    
    printf("DEBUG: File opened successfully, starting to read shift data\n");
    
    for (i=0; i<nfunc; i++)
    {
        printf("DEBUG: Reading shift data for function %d\n", i+1);
        
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
            
            if (j == 0 || j == nreal-1)
                printf("DEBUG: Read o[%d][%d] = %Lf\n", i, j, o[i][j]);
        }
        
        printf("DEBUG: Completed reading function %d\n", i+1);
    }
    
    fclose(fpt);
    
    printf("DEBUG: Setting lambda values\n");
    
    lambda[0] = 1.0;
    lambda[1] = 1.0;
    lambda[2] = 10.0;
    lambda[3] = 10.0;
    lambda[4] = 1.0/12.0;
    lambda[5] = 1.0/12.0;
    lambda[6] = 5.0/32.0;
    lambda[7] = 5.0/32.0;
    lambda[8] = 1.0/20.0;
    lambda[9] = 1.0/20.0;
    global_bias = 120.0;
    
    printf("DEBUG: initialize_f15 completed successfully\n");
    
    return;
}
void initialize_f16(void) 
{
    int i, j, k;
    FILE *fpt;
    
    /* Uses the same shift data as f15 */
    fpt = fopen("input_data/f15/shift_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file input_data/f15/shift_D50.txt for reading \n");
        exit(0);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
        }
        printf("\n");
    }
    fclose(fpt);
    if (nreal==2)    fpt = fopen("input_data/f16/rot_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/f16/rot_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/f16/rot_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/f16/rot_D50.txt","r");
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            for (k=0; k<nreal; k++)
            {
                fscanf(fpt,"%Lf",&l[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    lambda[0] = 1.0;
    lambda[1] = 1.0;
    lambda[2] = 10.0;
    lambda[3] = 10.0;
    lambda[4] = 1.0/12.0;
    lambda[5] = 1.0/12.0;
    lambda[6] = 5.0/32.0;
    lambda[7] = 5.0/32.0;
    lambda[8] = 1.0/20.0;
    lambda[9] = 1.0/20.0;
    global_bias = 120.0;
    return;
}
void initialize_f17(void) 
{
    int i, j, k;
    FILE *fpt;
    
    /* Uses the same shift data as f15 */
    fpt = fopen("input_data/f15/shift_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file input_data/f15/shift_D50.txt for reading \n");
        exit(0);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
        }
        printf("\n");
    }
    fclose(fpt);
    /* Same rotation data as f16 */
    if (nreal==2)    fpt = fopen("input_data/f16/rot_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/f16/rot_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/f16/rot_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/f16/rot_D50.txt","r");
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            for (k=0; k<nreal; k++)
            {
                fscanf(fpt,"%Lf",&l[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    lambda[0] = 1.0;
    lambda[1] = 1.0;
    lambda[2] = 10.0;
    lambda[3] = 10.0;
    lambda[4] = 1.0/12.0;
    lambda[5] = 1.0/12.0;
    lambda[6] = 5.0/32.0;
    lambda[7] = 5.0/32.0;
    lambda[8] = 1.0/20.0;
    lambda[9] = 1.0/20.0;
    global_bias = 120.0;
    return;
}
void initialize_f18(void) 
{
    int i, j, k;
    FILE *fpt;
    
    fpt = fopen("input_data/f18/shift_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file input_data/f18/shift_D50.txt for reading \n");
        exit(0);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
        }
        printf("\n");
    }
    fclose(fpt);
    if (nreal==2)    fpt = fopen("input_data/f18/rot_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/f18/rot_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/f18/rot_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/f18/rot_D50.txt","r");
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            for (k=0; k<nreal; k++)
            {
                fscanf(fpt,"%Lf",&l[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    for (i=0; i<nreal; i++)
    {
        o[nfunc-1][i] = 0.0;
    }
    sigma[0] = 1.0;
    sigma[1] = 2.0;
    sigma[2] = 1.5;
    sigma[3] = 1.5;
    sigma[4] = 1.0;
    sigma[5] = 1.0;
    sigma[6] = 1.5;
    sigma[7] = 1.5;
    sigma[8] = 2.0;
    sigma[9] = 2.0;
    lambda[0] = 5.0/16.0;
    lambda[1] = 5.0/32.0;
    lambda[2] = 2.0;
    lambda[3] = 1.0;
    lambda[4] = 1.0/10.0;
    lambda[5] = 1.0/20.0;
    lambda[6] = 20.0;
    lambda[7] = 10.0;
    lambda[8] = 1.0/6.0;
    lambda[9] = 1.0/12.0;
    global_bias = 10.0;
    return;
}
void initialize_f19(void) 
{
    int i, j, k;
    FILE *fpt;
    
    /* Same shift data as f18 */
    fpt = fopen("input_data/f18/shift_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file input_data/f18/shift_D50.txt for reading \n");
        exit(0);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
        }
        printf("\n");
    }
    fclose(fpt);
    /* Same rotation data as f18 */
    if (nreal==2)    fpt = fopen("input_data/f18/rot_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/f18/rot_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/f18/rot_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/f18/rot_D50.txt","r");
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            for (k=0; k<nreal; k++)
            {
                fscanf(fpt,"%Lf",&l[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    for (i=0; i<nreal; i++)
    {
        o[nfunc-1][i] = 0.0;
    }
    sigma[0] = 0.1;
    sigma[1] = 2.0;
    sigma[2] = 1.5;
    sigma[3] = 1.5;
    sigma[4] = 1.0;
    sigma[5] = 1.0;
    sigma[6] = 1.5;
    sigma[7] = 1.5;
    sigma[8] = 2.0;
    sigma[9] = 2.0;
    lambda[0] = 0.5/32.0;
    lambda[1] = 5.0/32.0;
    lambda[2] = 2.0;
    lambda[3] = 1.0;
    lambda[4] = 1.0/10.0;
    lambda[5] = 1.0/20.0;
    lambda[6] = 20.0;
    lambda[7] = 10.0;
    lambda[8] = 1.0/6.0;
    lambda[9] = 1.0/12.0;
    global_bias = 10.0;
    return;
}
void initialize_f20(void) 
{
    int i, j, k;
    int index;
    FILE *fpt;
    
    /* Same shift data as f18 */
    fpt = fopen("input_data/f18/shift_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file input_data/f18/shift_D50.txt for reading \n");
        exit(0);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
        }
        printf("\n");
    }
    fclose(fpt);
    index = nreal/2;
    for (i=1; i<=index; i++)
    {
        o[0][2*i-1] = 5.0;
    }
    /* Same rotation data as f18 */
    if (nreal==2)    fpt = fopen("input_data/f18/rot_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/f18/rot_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/f18/rot_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/f18/rot_D50.txt","r");
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            for (k=0; k<nreal; k++)
            {
                fscanf(fpt,"%Lf",&l[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    for (i=0; i<nreal; i++)
    {
        o[nfunc-1][i] = 0.0;
    }
    sigma[0] = 1.0;
    sigma[1] = 2.0;
    sigma[2] = 1.5;
    sigma[3] = 1.5;
    sigma[4] = 1.0;
    sigma[5] = 1.0;
    sigma[6] = 1.5;
    sigma[7] = 1.5;
    sigma[8] = 2.0;
    sigma[9] = 2.0;
    lambda[0] = 5.0/16.0;
    lambda[1] = 5.0/32.0;
    lambda[2] = 2.0;
    lambda[3] = 1.0;
    lambda[4] = 1.0/10.0;
    lambda[5] = 1.0/20.0;
    lambda[6] = 20.0;
    lambda[7] = 10.0;
    lambda[8] = 1.0/6.0;
    lambda[9] = 1.0/12.0;
    global_bias = 10.0;
    return;
}
void initialize_f21(void) 
{
    int i, j, k;
    FILE *fpt;
    
    fpt = fopen("input_data/f21/shift_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file input_data/f21/shift_D50.txt for reading \n");
        exit(0);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
        }
        printf("\n");
    }
    fclose(fpt);
    if (nreal==2)    fpt = fopen("input_data/f21/rot_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/f21/rot_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/f21/rot_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/f21/rot_D50.txt","r");
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            for (k=0; k<nreal; k++)
            {
                fscanf(fpt,"%Lf",&l[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    sigma[0] = 1.0;
    sigma[1] = 1.0;
    sigma[2] = 1.0;
    sigma[3] = 1.0;
    sigma[4] = 1.0;
    sigma[5] = 2.0;
    sigma[6] = 2.0;
    sigma[7] = 2.0;
    sigma[8] = 2.0;
    sigma[9] = 2.0;
    lambda[0] = 1.0/4.0;
    lambda[1] = 1.0/20.0;
    lambda[2] = 5.0;
    lambda[3] = 1.0;
    lambda[4] = 5.0;
    lambda[5] = 1.0;
    lambda[6] = 50.0;
    lambda[7] = 10.0;
    lambda[8] = 1.0/8.0;
    lambda[9] = 1.0/40.0;
    global_bias = 360.0;
    return;
}
void initialize_f22(void) 
{
    int i, j, k;
    FILE *fpt;
    
    /* Same shift data as f21 */
    fpt = fopen("input_data/f21/shift_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file input_data/f21/shift_D50.txt for reading \n");
        exit(0);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
        }
        printf("\n");
    }
    fclose(fpt);
    if (nreal==2)    fpt = fopen("input_data/f22/rot_sub_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/f22/rot_sub_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/f22/rot_sub_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/f22/rot_sub_D50.txt","r");
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            for (k=0; k<nreal; k++)
            {
                fscanf(fpt,"%Lf",&l[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    sigma[0] = 1.0;
    sigma[1] = 1.0;
    sigma[2] = 1.0;
    sigma[3] = 1.0;
    sigma[4] = 1.0;
    sigma[5] = 2.0;
    sigma[6] = 2.0;
    sigma[7] = 2.0;
    sigma[8] = 2.0;
    sigma[9] = 2.0;
    lambda[0] = 1.0/4.0;
    lambda[1] = 1.0/20.0;
    lambda[2] = 5.0;
    lambda[3] = 1.0;
    lambda[4] = 5.0;
    lambda[5] = 1.0;
    lambda[6] = 50.0;
    lambda[7] = 10.0;
    lambda[8] = 1.0/8.0;
    lambda[9] = 1.0/40.0;
    global_bias = 360.0;
    return;
}
void initialize_f23(void) 
{
    int i, j, k;
    FILE *fpt;
    
    /* Same shift data as f21 */
    fpt = fopen("input_data/f21/shift_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file input_data/f21/shift_D50.txt for reading \n");
        exit(0);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
        }
        printf("\n");
    }
    fclose(fpt);
    /* Same rotation data as f21 */
    if (nreal==2)    fpt = fopen("input_data/f21/rot_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/f21/rot_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/f21/rot_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/f21/rot_D50.txt","r");
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            for (k=0; k<nreal; k++)
            {
                fscanf(fpt,"%Lf",&l[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    sigma[0] = 1.0;
    sigma[1] = 1.0;
    sigma[2] = 1.0;
    sigma[3] = 1.0;
    sigma[4] = 1.0;
    sigma[5] = 2.0;
    sigma[6] = 2.0;
    sigma[7] = 2.0;
    sigma[8] = 2.0;
    sigma[9] = 2.0;
    lambda[0] = 1.0/4.0;
    lambda[1] = 1.0/20.0;
    lambda[2] = 5.0;
    lambda[3] = 1.0;
    lambda[4] = 5.0;
    lambda[5] = 1.0;
    lambda[6] = 50.0;
    lambda[7] = 10.0;
    lambda[8] = 1.0/8.0;
    lambda[9] = 1.0/40.0;
    global_bias = 360.0;
    return;
}
void initialize_f24(void) 
{
    int i, j, k;
    FILE *fpt;
    
    fpt = fopen("input_data/f24/shift_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file input_data/f24/shift_D50.txt for reading \n");
        exit(0);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
        }
        printf("\n");
    }
    fclose(fpt);
    if (nreal==2)    fpt = fopen("input_data/f24/rot_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/f24/rot_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/f24/rot_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/f24/rot_D50.txt","r");
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            for (k=0; k<nreal; k++)
            {
                fscanf(fpt,"%Lf",&l[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    for (i=0; i<nfunc; i++)
    {
        sigma[i] = 2.0;
    }
    lambda[0] = 10.0;
    lambda[1] = 1.0/4.0;
    lambda[2] = 1.0;
    lambda[3] = 5.0/32.0;
    lambda[4] = 1.0;
    lambda[5] = 1.0/20.0;
    lambda[6] = 1.0/10.0;
    lambda[7] = 1.0;
    lambda[8] = 1.0/20.0;
    lambda[9] = 1.0/20.0;
    global_bias = 260.0;
    return;
}
void initialize_f25(void) 
{ 
    /* F25 is the same as F24 for initialization purposes */
    initialize_f24();
}
