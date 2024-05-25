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

        unsigned long long int unsig_rand1 = ((unsigned long long int)rand1) & 0xFFFFFFFF;
        unsigned long long int unsig_rand2 = (unsigned long long int)rand2 & 0xFFFFFFF;
        //printf("\n rand1: %llu \n", unsig_rand1);
        //printf("\n rand2: %llu  \n", unsig_rand2);
        unsigned long long int shift_unsig_rand1 = unsig_rand1 << 32;
        x = shift_unsig_rand1 | unsig_rand2;
        //printf("\n x: %llu \n", x);
        return x;
    }

    void mrand_rand64_fini (void){
    }