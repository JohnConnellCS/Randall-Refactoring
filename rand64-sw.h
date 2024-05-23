#ifndef RAND_SW
#define RAND_SW
#include <stdlib.h>
#include <stdio.h>
    void
    software_rand64_init (const char *filepath);
    unsigned long long
    software_rand64 (void);
    void
    software_rand64_fini (void);
#endif