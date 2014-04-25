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

  free(data);

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
  Node * data = malloc(sizeof(Node) * (2 * num * (num - 1)));

  int i;

  for(i = 0; i < (num * (num - 1)); i++)
  {
    fscanf(fptr, "%d", &data[i].branch);

    data[i].tr = num * (num - 1) + i / num + (i % num) * num;
    data[i].br = data[i].tr + 1;

    data[i].tl = num * (num - 1) + (i % num - 1) * num + i / num;
    data[i].bl = data[i].tl + 1;

    if(i % num == 0)
    {
      // Change to left bank
      data[i].bl = -1;
      data[i].tl = -1;
    }
    else if(i % num == (num - 1))
    {
      // Change to right bank
      data[i].br = -1;
      data[i].tr = -1;
    }
  }

  for(i = (num * (num - 1)); i < (2 * num * (num - 1)); i++)
  {
    data[i].tl = (i % num - 1) * num + i / (num * num);
    data[i].tr = data[i].tl + 1;

    data[i].bl = (i % num) * num + i / (num * num);
    data[i].br = data[i].bl + 1;

    if(i % num == 0)
    {
      data[i].tl = -1;
      data[i].tr = -1;
    }
    else if(i % num == (num -1))
    {
      data[i].bl = -1;
      data[i].br = -1;
    }
  }

  return data;
}
