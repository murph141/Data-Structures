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
  char * output_file = argv[2];
  
  Node * Values = Load_File(input_file);

  if(Values == NULL)
  {
    printf("Load_File function execution unsuccessful\n");
    free(Values);
    return EXIT_FAILURE;
  }

  Special_Post_Order(Values, Values[0].parent);

  int max_depth = 0;

  Deepest_Node(Values, Values[0].parent, 0, &max_depth);

  printf("%d %d\n", max_depth, Values[0].right);

  int test = Save_File(Values, output_file);

  if(test == 1)
  {
    printf("Save_File function execution unsuccessful\n");
    return EXIT_FAILURE;
  }

  Screen_Dump(Values);

  free(Values);
  return EXIT_SUCCESS;
}
