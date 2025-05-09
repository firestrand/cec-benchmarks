/* Declaration for random number related variables and routines */

# ifndef _RAND_H
# define _RAND_H

# include "global.h"

/* Variable declarations for the random number generator */

/* Function declarations for the random number generator */
void randomize(void);
long double randomperc(void);
int rnd (int low, int high);
long double rndreal (long double low, long double high);
void initrandomnormaldeviate(void);
long double noise (long double mu, long double sigma);
long double randomnormaldeviate(void);

# endif
