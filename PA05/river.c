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

  int best = Load_File(input);

  if(best == -1)
  {
    return EXIT_FAILURE;
  }

  printf("%d\n", best);

  return EXIT_SUCCESS; // WE'VE SUCCEEDED!!!!!
}


int Load_File(char * input)
{
  FILE * fptr = fopen(input, "r");

  if(fptr == NULL)
  {
    printf("Error: Failed to Open File!\n");
    return -1;
  }

  int num;

  fscanf(fptr, "%d", &num);

  Node * data;

  data = Create_Graph(num, fptr);

  if(data == NULL)
  {
    return -1;
  }

  int i, temp;
  int best = 2 * num;
  
  for(i = 0; i < (2 * num * (num - 1)); i += num)
  {
    temp = Dijkstra(&data[i], data) + (1 - data[i].branch);

    if(temp < best)
    {
      best = temp;
    }
  }
  // All errors need to free data from here on out
  free(data);

  return best; // Change to the number here
}


// Creates the entire graph
Node * Create_Graph(int num, FILE * fptr)
{
  Node * data = calloc(sizeof(Node) * (2 * num * (num - 1)), sizeof(Node));

  if(data == NULL)
  {
    printf("Error: Memory Allocation Failed!\n");
    return NULL;
  }

  int i;

  // Iterate over the first set of nodes
  // Scan in the values of the planks (branches)
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

  fclose(fptr); //File I/O is finished

  // Iterate over the second set of nodes
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

  // Add in the weights of the edges
  Weights_Right(data, num);
  Weights_Left(data, num);

  for(i = 0; i < (num * (num - 1)); i++)
  {
    data[i].distance = 10 * num;
    if(i % num == 0)
    {
      // Change to left bank
      data[i].blw = -1;
      data[i].tlw = -1;
    }
  }

  // Make the nodes connecting to the outside of the graph negligible
  for(i = (num * (num - 1)); i < (2 * num * (num - 1)); i++)
  {
    data[i].distance = 10 * num;
    if(i % num == 0)
    {
      data[i].trw = -1;
      data[i].tlw = -1;
    }
    else if(i % num == (num - 1))
    {
      data[i].blw = -1;
      data[i].brw = -1;
    }
  }

  return data;
}


// Calcuate the weights of the edges that move from left to right
void Weights_Right(Node * data, int num)
{
  int i;

  // Iterate over the edges
  for(i = 0; i < (2 * num * (num - 1)); i++)
  {
    data[i].trw = 1;
    data[i].brw = 1;

    if(data[i].tr != -1 && data[data[i].tr].branch == 1)
    {
      data[i].trw = 0;
    }

    if(data[i].br != -1 && data[data[i].br].branch == 1)
    {
      data[i].brw = 0;
    }
  }
}


// Calcuate the weights of the edges that move from right to left
void Weights_Left(Node * data, int num)
{
  int i;

  // Iterate over the edges
  for(i = 0; i < (2 * num * (num - 1)); i++)
  {
    data[i].tlw = 1;
    data[i].blw = 1;

    if(data[i].tl != -1)
    {
      if(data[data[i].tl].branch == 1)
      {
        data[i].tlw = 0;
      }
    }

    if(data[i].bl != -1 && data[data[i].bl].branch == 1)
    {
      data[i].blw = 0;
    }
  }
}

int Dijkstra(Node * data, Node * start)
{
  return 0;
}
