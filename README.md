DEV LOG: 
* Setup and downloading the starter code
   * Make a directory and move into it
   * Use wget with the link to the tarball file
   * Unpack the tarball and use git reset --hard to navigate to the correct location
   * If you type ls, you should see four files
* randall and Makefiles
   * Run ‘make’ to build
   * Test ./randall(displays help info) and ./randall n where n is an integer for the number of bytes you want
* Unit testing
   * To create a unit test, go into the Makefile
      * Add ‘check: randall’ followed by the code for the text
      * For NBYTE(checks if the number of bytes is correct)
         * Pipe the output of ./randall into wc -c and then use grep to check if the output is 20
   * After saving Makefile, ensure that ./randall passes the test. If so, git add and git commit the new test.
* Refactor randall into multiple files and modify the Makefile
   * Refactor hardware
      * Create rand64-hw header and c files
      * Copy Funcntion related to hardware from randall.c(all at the top under a comment) and paste into the c files
      * Add function and struct declarations into header file, an include guard, and the cpuid.h and immintrin.h libraries
         * *In C, you have to say struct when returning a struct type, differently from C++. 
         * Ex. struct cpuid cpuid (unsigned int leaf, unsigned int subleaf){}
   * Refactor software
      * Create rand64-sw header and c files
      * Copy Funcntion related to software from randall.c(under the hardware functions but above writebytes)
      * Add function declarations into header file, an include guard, and the stdlib.h and stdio.h libraries
      * Copy The randall.c function starting from the comment “/* Now that we know we have work to do” and ending at “return !!output_errno;”. Put this code into “int handle_output(int nbytes)”. We are moving this into the outfile as it determines return value and output. Back in randall.c, return the result of calling handle_output with nbytes.
   * Refactor output
      * Create output header and c files
      * Add function declarations into header file, an include guard, and the stdbool.h, stdlib.h, stdio.h, errno.h, rand64-hw, and rand 64-sw libraries(we’ll use these in a second)
      * Copy The randall.c function starting from the comment “/* Now that we know we have work to do” and ending at “return !!output_errno;”. Put this code into “int handle_output(int nbytes)”. We are moving this into the outfile as it determines return value and output. Back in randall.c, return the result of calling handle_output with nbytes.
   * Refactor options
      * Create options header and c files
      * Add function declarations into header file, an include guard, and the stdbool.h, stdlib.h, stdio.h, errno.h
      * Copy the processing of nbytes into output.c(this is from the start of main to the check for nbytes==0.) Put this into the function long long handle_nbytes(int argc, char **argv) in the .c file.
   * Updating makefile
      * Overwrite the lines that says “randall: randall.c” with the following chunk of code. This ensures that all files are used when running make.
         * # Relevant files.
         * FILES = $(wildcard *.c) $(wildcard *.h)
         *          * randall: randall.c $(FILES)
         *         $(CC) $(CFLAGS) *.c -o $@
