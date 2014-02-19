#include<stdio.h>
#include<stdlib.h>
#include "pa01.h"

int main(int argc, char * argv[])
{
  if(argc != 5)
  {
    printf("Usage: ./proj1 <sorting_method> <input_file> <sequence_file> <output_file>\n");
    return EXIT_FAILURE;
  }

  //const char * method = argv[1];
  const char * input_file = argv[2];
  //const char * sequence_file = argv[3];
  //const char * output_file = argv[4];

  FILE * iptr = fopen(input_file, "r+");

  if(iptr == NULL)
  {
    printf("Error opening input file\n");
    return EXIT_FAILURE;
  }

  int valid = validate_numbers(iptr);

  if(valid)
  {
    printf("Number of items scanned does not equal number of items specified\n");
    return EXIT_FAILURE;
  }

  int * Size;
  Load_File(input_file, Size);
  // FCLOSE
  fclose(iptr);
  return 0;
}
