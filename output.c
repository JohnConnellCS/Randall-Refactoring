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
  void (*initialize) (void);
  unsigned long long (*rand64) (void);
  void (*finalize) (void);
  if (strcmp(input, "rdrand") == 0 && rdrand_supported ())
    {
      //rdrand option
      initialize = hardware_rand64_init;
      rand64 = hardware_rand64;
      finalize = hardware_rand64_fini;
    }
  else  if(strcmp(input, "lrand48_r") == 0)
    {
      //lrand48_r option
      initialize = software_rand64_init;
      rand64 = software_rand64;
      finalize = software_rand64_fini;
    } else {
      //file option
      //CHECK FOR ERRORS USING BELOW
  }
/*else if(strcmp(input[0],'/') == 0){
      
      int fd = open(input, O_RDONLY);
      if(fd == -1){
        perror("open");
        return 1;
      }
      initialize = file_rand64_init;
      rand64 = file_rand64;
      finalize = file_rand64_fini;
      set_file_descriptor(fd)
      
  }*/
  initialize ();
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
  //deal with N options case
}
  finalize ();
  return !!output_errno;
}