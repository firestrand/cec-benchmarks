/* Sample main to demonstrate the use of various functions */
/* Please go through this file carefully */
/* It demonstrates the use of various routines */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# include "global.h"
# include "sub.h"
# include "rand.h"

void print_usage(char* progname) {
    fprintf(stderr, "\nUsage: %s <function_id> <dimension> [input_file]\n", progname);
    fprintf(stderr, "   <function_id>: An integer from 1 to 25\n");
    fprintf(stderr, "   <dimension>: The problem dimension (2, 10, 30, or 50)\n");
    fprintf(stderr, "   [input_file]: Optional file containing input vector values (one per line)\n");
    exit(1);
}

int main(int argc, char** argv)
{
	int i;
	long double *x;
	long double f;
	FILE *input_file = NULL;
	
	/* Check command line arguments */
	if (argc < 3) {
		print_usage(argv[0]);
	}
	
	/* Parse function ID and dimension */
	function_id = atoi(argv[1]);
	nreal = atoi(argv[2]);
	
	/* Validate function ID */
	if (function_id < 1 || function_id > 25) {
		fprintf(stderr, "\nError: Function ID must be between 1 and 25, got %d\n", function_id);
		print_usage(argv[0]);
	}
	
	/* Validate dimension */
	if (nreal != 2 && nreal != 10 && nreal != 30 && nreal != 50) {
		fprintf(stderr, "\nError: Dimension must be 2, 10, 30, or 50, got %d\n", nreal);
		print_usage(argv[0]);
	}
	
	/* Set nfunc based on function_id */
	if (function_id <= 14) {
		nfunc = 1;  /* Single function for F1-F14 */
	} else {
		nfunc = 10; /* Composite functions for F15-F25 */
	}
	
	printf("\nRunning function F%d with %d variables\n", function_id, nreal);
	
	/* Initialize random number generators for noise functions */
	randomize();
	initrandomnormaldeviate();
	
	/* Allocate memory for global variables */
	allocate_memory();
	
	/* Initialize variables for the selected function */
	initialize();
	
	/* Calculate normalization for composite functions (F15-F25) */
	if (function_id >= 15) {
		calc_benchmark_norm();
	}
	
	/* Allocate memory for input vector */
	x = (long double *)malloc(nreal * sizeof(long double));
	
	/* Check if an input file was provided */
	if (argc > 3) {
		input_file = fopen(argv[3], "r");
		if (!input_file) {
			fprintf(stderr, "\nError: Cannot open input file %s\n", argv[3]);
			exit(1);
		}
		
		for (i = 0; i < nreal; i++) {
			if (fscanf(input_file, "%Lf", &x[i]) != 1) {
				fprintf(stderr, "\nError: Failed to read value %d from input file\n", i+1);
				fclose(input_file);
				exit(1);
			}
			printf("x[%d] = %Lf\n", i+1, x[i]);
		}
		fclose(input_file);
	} else {
		/* Read from standard input */
		for (i = 0; i < nreal; i++) {
			printf("\nEnter the value of variable x[%d] : ", i+1);
			scanf("%Lf", &x[i]);
		}
	}
	
	/* Calculate objective function value */
	f = calc_benchmark_func(x);
	printf("\nObjective value = %1.15LE\n", f);
	
	/* Free memory */
	free_memory();
	free(x);
	
	printf("\nRoutine exited without any error.\n");
	return 0;
}
