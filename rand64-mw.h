#ifndef RAND_MW
#define RAND_MW
#include <stdio.h>
#include <stdlib.h> // for mrand48_r
#include <time.h> // for time

extern struct drand48_data state;
void
mrand_rand64_init (void);
unsigned long long
mrand_rand64 (void);
void
mrand_rand64_fini (void);

#endif