#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "pa02.h"

int main(int argc, char * argv[])
{
  if(argc != 3)
  {
    printf("\nUsage: ./proj2 <input_file> <output_file>\n\n");
    return EXIT_FAILURE;
  }
  
  char * input_file = argv[1];
  //char * output_file = argv[2];

  Node * values = Load_File(input_file);

  if(!values)
  {
    printf("Error in Load_File function\n");
    return EXIT_FAILURE;
  }

  Destroy_Struct(values);

  return EXIT_SUCCESS;
}
