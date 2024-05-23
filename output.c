#include "output.h"

bool
writebytes (unsigned long long x, int nbytes)
{
  do
    {
      if (putchar (x) < 0)
	return false;
      x >>= CHAR_BIT;
      nbytes--;
    }
  while (0 < nbytes);

  return true;
}

int handle_output(int nbytes, char *input, char *output)
{
    /* Now that we know we have work to do, arrange to use the
     appropriate library.  */
  void (*initialize) (const char *);
  unsigned long long (*rand64) (void);
  void (*finalize) (void);

  if(strcmp(input,"") == 0 || strcmp(output,"") == 0){
    return -1;
  }

  if (strcmp(input, "rdrand") == 0 && rdrand_supported ())
    {
      //rdrand option
      initialize = (void (*)(const char *))hardware_rand64_init;
      rand64 = hardware_rand64;
      finalize = hardware_rand64_fini;
    }
  else  if(strcmp(input, "lrand48_r") == 0)
    {
      //lrand48_r option
      initialize = software_rand64_init;
      rand64 = software_rand64;
      finalize = software_rand64_fini;
      //NEED INITIALIZE STATEMENT
    } else {
      //file option
      if (input[0] != '/') {
        return -1;
      }
      initialize = software_rand64_init;
      rand64 = software_rand64;
      finalize = software_rand64_fini;
  }

  initialize(input);
  int wordsize = sizeof rand64 ();
  int output_errno = 0;


if(strcmp(output, "stdio") == 0){
  do
    {
      unsigned long long x = rand64 ();
      int outbytes = nbytes < wordsize ? nbytes : wordsize;
      if (!writebytes (x, outbytes))
	{
	  output_errno = errno;
	  break;
	}
      nbytes -= outbytes;
    }
  while (0 < nbytes);

  if (fclose (stdout) != 0)
    output_errno = errno;

  if (output_errno)
    {
      errno = output_errno;
      perror ("output");
    }
}else{
  //N case
}
  finalize ();
  return !!output_errno;
}