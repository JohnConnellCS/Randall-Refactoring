#ifndef OUTPUT
#define OUTPUT
#include <stdbool.h>
#include <limits.h>
#include <stdio.h>

#include <cpuid.h>
#include <errno.h>
#include <immintrin.h>
#include <stdlib.h>
#include "rand64-hw.h"
#include "rand64-sw.h"

int handle_output(int nbytes);
bool 
writebytes (unsigned long long x, int nbytes);
int handle_output(int nbytes);
#endif 