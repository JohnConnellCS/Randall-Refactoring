#include "rand64-mw.h"
struct drand48_data state;

    void mrand_rand64_init (void){
        srand48_r(time(NULL), &state);
    }

    unsigned long long mrand_rand64 (void){
        unsigned long long int x;


        long int rand1;
        int val1;
        val1 = mrand48_r(&state, &rand1);
        if(val1 < 0){
            return -1;
        }

        long int rand2;
        int val2;
        val2 = mrand48_r(&state, &rand2);
        if(val2 < 0){
            return -1;
        }

        long long unsig_rand1 = rand1 << 32;
        long long unsig_rand2 = rand2;
        //printf("rand1: %lu ", unsig_rand1);
        //printf("rand2: %lu ", unsig_rand2);

        x = unsig_rand1 | unsig_rand2;
        printf("x: %llu \n", x);
        return x;
    }

    void mrand_rand64_fini (void){
    }