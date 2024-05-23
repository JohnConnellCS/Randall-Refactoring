/* Generate N bytes of random output.  */

/* When generating output this program uses the x86-64 RDRAND
   instruction if available to generate random numbers, falling back
   on /dev/random and stdio otherwise.

   This program is not portable.  Compile it with gcc -mrdrnd for a
   x86-64 machine.

   Copyright 2015, 2017, 2020 Paul Eggert

   This program is free software: you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include <cpuid.h>
#include <errno.h>
#include <immintrin.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>

#include "rand64-hw.h"
#include "rand64-sw.h"
#include "output.h"
#include "options.h"

/* Main program, which outputs N bytes of random data.  */
int
main (int argc, char **argv)
{
  /* parse for options*/
  int argVal;
  char *input = "rdrand";
  char *output = "stdio";
  char *custom_file = NULL;

  while ((argVal = getopt (argc, argv, "i:o:")) != -1)
  {
    switch(argVal)
    {
    case 'i':
      input = optarg;
      break;
    case 'o':
      output = optarg;
      break;
    }
  }

  if(input[0] == '/'){
    custom_file = input;
    input = "file";
  }

  /* Check arguments.  */
  long long nbytes;
  nbytes = handle_nbytes(argc, argv);
  if(nbytes == 0){
    return 0;
  }
  if(nbytes == -1){
    return 1;
  }

  return handle_output(nbytes, input);
}


long long get_nbytes(int argc, char **argv) {
    if (optind < argc) {
        char *endptr;
        long long nbytes = strtoll(argv[optind], &endptr, 10);
        if (*endptr != '\0' || nbytes < 0) {
            fprintf(stderr, "Invalid number of bytes: %s\n", argv[optind]);
            return 0;
        }
        return nbytes;
    }
    fprintf(stderr, "Usage: %s [-i input] [-o output] <nbytes>\n", argv[0]);
    return 0;
}