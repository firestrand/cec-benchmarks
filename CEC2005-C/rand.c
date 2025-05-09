/* Definition of random number generation routines */

# include <stdio.h>
# include <stdlib.h> /* For rand(), srand(), RAND_MAX */
# include <math.h>
# include <time.h>   /* For time() */

# include "global.h"
# include "rand.h"

/* Static variables for Box-Muller transform */
static int rndcalcflag_local;
static long double rndx1_local, rndx2_local;

/* Get seed number for random and start it up */
void randomize(void)
{
    srand((unsigned int)time(NULL));
    return;
}

/* Fetch a single random number between 0.0 and 1.0 */
long double randomperc(void)
{
    return ((long double)rand() / (long double)RAND_MAX);
}

/* Fetch a single random integer between low and high including the bounds */
int rnd (int low, int high)
{
    int res;
    if (low >= high)
    {
        res = low;
    }
    else
    {
        /* Ensure randomperc() is in [0,1) for correct distribution before scaling */
        /* then map to [0, high-low], then shift by low */
        /* (int)(randomperc() * (high - low + 1)) + low might be slightly biased if randomperc() can be 1.0 */
        /* A common way for [low, high]: low + rand() % (high - low + 1) */
        res = low + (rand() % (high - low + 1));
        /* The original logic for clamping, though should not be strictly necessary with rand() % */
        if (res > high)
        {
            res = high;
        }
         if (res < low) /* Should not happen with % (H-L+1) + L */
        {
            res = low;
        }
    }
    return (res);
}

/* Fetch a single random real number between low and high including the bounds */
long double rndreal (long double low, long double high)
{
    return (low + (high-low)*randomperc());
}

/* Initialize the random generator for normal distribution */
void initrandomnormaldeviate(void)
{
    rndcalcflag_local = 1;
    return;
}

/* Return the noise value */
long double noise (long double mu, long double sigma)
{
    return((randomnormaldeviate()*sigma) + mu);
}

/* Compute the noise using Box-Muller transform */
long double randomnormaldeviate(void)
{
    long double t;
    if(rndcalcflag_local)
    {
        /* Ensure randomperc() > 0 for log() */
        long double r1 = 0.0L, r2 = 0.0L;
        while (r1 == 0.0L) r1 = randomperc(); /* Avoid log(0) */
        r2 = randomperc();

        rndx1_local = sqrt(-2.0L * log(r1));
        t = 2.0L * M_PI * r2; /* M_PI is from math.h, ensure it's available or defined */
        rndx2_local = sin(t);
        rndcalcflag_local = 0;
        return(rndx1_local * cos(t));
    }
    else
    {
        rndcalcflag_local = 1;
        return(rndx1_local * rndx2_local);
    }
}
