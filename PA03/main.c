#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "packing.h"

int main(int argc, char * argv[])
{
  if(argc != 3)
  {
    printf("Usage: ./proj3 <input_file> <output_file>\n");
    return EXIT_FAILURE;
  }

  char * input_file = argv[1];
  
  Node * Values = Load_File(input_file);

  if(Values == NULL)
  {
    printf("Load_File function execution unsuccessful\n");
    free(Values);
    return EXIT_FAILURE;
  }

  Screen_Dump(Values);

  Special_Post_Order(Values, Values[0].width);

  free(Values);
  return EXIT_SUCCESS;
}
