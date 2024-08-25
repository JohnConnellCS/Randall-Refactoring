Expanded randall command by implementing the following:

Run 'make' before running command. Format command as the following:

./randall n -i input -o output
Where n is the number of characters to output, input is the input option, and output is the output option

Implemented 2 new input options which can be used with '-i input', where input is one of the following:

1. rdrand – the hardware random-number generation supported by x86-64 processors if available; randall should issue an error message and fail if it is not available.(original input format)
2. /F (i.e., any argument beginning with /) – use the file /F as a source of random data, instead of using /dev/random.
3. lrand48_r – the lrand48_r function of the GNU C library(bitwise implementation).

Implemented 1 new Output Options which can be used with '-o output', where output is one of the following:

1. stdio – Use stdio output, as before(original output format)
2. N (a positive decimal integer) – Output N bytes at a time, using the write system call(utilizes malloc).
