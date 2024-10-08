#ifndef OUTPUT
#define OUTPUT
#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "rand64-hw.h"
#include "rand64-sw.h"
#include "rand64-mw.h"

bool 
writebytes (unsigned long long x, int nbytes);
int handle_output(int nbytes, char *input, char *output);
#endif 