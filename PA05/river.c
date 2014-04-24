#include<stdio.h>
#include<stdlib.h>
#include "river.h"

int main(int argc, char * argv[])
{
  if(argc != 2)
  {
    printf("Usage: proj5 <input_file>\n");
    return EXIT_FAILURE;
  }

  char * input = argv[1];

  Node * data = Load_File(input);

  if(data == NULL)
  {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS; // WE'VE SUCCEEDED!!!!!
}


Node * Load_File(char * input)
{
  FILE * fptr = fopen(input, "r");

  if(fptr == NULL)
  {
    printf("Error: Memory Allocation Failed!\n");
    return NULL;
  }

  int num;

  fscanf(fptr, "%d", &num);

  Node * data;

  data = Create_Graph(num, fptr);

  fclose(fptr);

  return data;
}


Node * Create_Graph(int num, FILE * fptr)
{

  return NULL;
}
