#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "pa01.h"

int main(int argc, char * argv[])
{
  if(argc != 5)
  {
    printf("Usage: ./proj1 <sorting_method> <input_file> <sequence_file> <output_file>\n");
    return EXIT_FAILURE;
  }

  //char * method = argv[1];
  char * input_file = argv[2];
  char * sequence_file = argv[3];
  //char * output_file = argv[4];

  int Size;
  long * values;

  values = Load_File(input_file, &Size);

  if(values == NULL)
  {
    return EXIT_FAILURE;
  }

  //clock_t initial_time, after_sequence;

  //initial_time = clock();
  // NEED TO FREE AFTER THIS POINT
  int i = Print_Seq(sequence_file, Size);
  
  if(i == 0)
  {
    printf("Failed to print sequence\n");
    free(values);
    return EXIT_FAILURE;
  }


  return EXIT_SUCCESS;
}
