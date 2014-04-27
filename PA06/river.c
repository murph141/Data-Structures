#include<stdio.h>
#include<stdlib.h>
#include "river.h"

int ones = 0, num;

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

  fscanf(fptr, "%d", &num);

  Node * data;

  data = Create_Graph(fptr);

  Calculate_Distance(data, ones + 2);

  if(data == NULL)
  {
    return -1;
  }

  int best = num * 2;

  // May need to add one to account for missing 1 earlier
  return best; // Change to the number here
}


// Creates the entire graph
Node * Create_Graph(FILE * fptr)
{
  char a = 0;

  while(a != EOF)
  {
    a = fgetc(fptr);

    if(a == 49 && ones++);
  }

  printf("%d\n", ones);

  fseek(fptr, 0, SEEK_SET);

  a = fgetc(fptr);

  while(a != '\n')
  {
    a = fgetc(fptr);
  }

  Node * data = calloc(ones + 2, sizeof(Node));

  int col = 0, row = 0, index = 0;

  while(a != EOF)
  {
    a = fgetc(fptr);

    if(a == '\n')
    {
      row++;
      col = -1;
    }

    if(a == 49)
    {
      data[index].x = col;
      data[index].y = row;
      index++;
    }

    col++;
  }

  fclose(fptr);

  data[ones].x = -1;
  data[ones].y = -1;

  data[ones + 1].x = -1;
  data[ones + 1].y = -1;

  Create_Adjacency(data, ones + 2);

  return data;
}


void Create_Adjacency(Node * data, int nodes)
{
  int i, j, index;

  for(i = 0; i < nodes; i++)
  {
    data[i].adj = malloc(sizeof(int) * (nodes - 1));
    data[i].dist = calloc(nodes - 1, sizeof(int));
    index = 0;

    for(j = 0; j < nodes; j++)
    {
      if(i != j)
      {
        data[i].adj[index++] = j;
      }
    }
  }
}


void Calculate_Distance(Node * data, int nodes)
{
  int index, inner;

  // Calculate distances for the banks

  for(index = 0; index < nodes; index++)
  {
    for(inner = 0; inner < (nodes - 1); inner++)
    {
      if(index == (nodes - 2))
      {
        if(inner == (nodes - 2))
        {
          data[index].dist[inner] = 2 * num;
        }
        else
        {
          data[index].dist[inner] = 2 * data[data[index].adj[inner]].x;
        }
      }
      else if(index == (nodes - 1))
      {
        if(inner == (nodes - 2))
        {
          data[index].dist[inner] = 2 * num;
        }
        else
        {
          data[index].dist[inner] = 2 * (num - 1 - data[data[index].adj[inner]].x);
        }
      }
      else
      {
        if(inner == (nodes - 3))
        {
          data[index].dist[inner] = 2 * data[index].x;
        }
        else if (inner == (nodes - 2))
        {
          data[index].dist[inner] = 2 * (num - 1 - data[index].x);
        }
        else
        {
          // Non-bank nodes
          if(IsInCone(data[index].x, data[index].y, data[data[index].adj[inner]].x, data[data[index].adj[inner]].y))
          {
            data[index].dist[inner] = 2 * abs(data[data[index].adj[inner]].x - data[index].x) - 1;
          }
          else
          {
            // Have to check for both top and bottom
            //if(data[index].y > data[data[index].adj[inner]].y)
            int changex = abs(data[data[index].adj[inner]].x - data[index].x);
            int changey = abs(data[data[index].adj[inner]].y - data[index].y);
            data[index].dist[inner] = 2 * changex + 2 * (changey - 2);
            /*
               else
               {
               int changex = abs(data[data[index].adj[inner]].x - data[index].x);
               int changey = abs(data[data[index].adj[inner]].y - data[index].y);
               data[index].dist[inner] = 2 * changex + 2 * (changey - 2);
               }
               */
          }
        }
      }
    }
  }

  //Cone(data, nodes - 2);
}


int IsInCone(int x1, int y1, int x2, int y2)
{
  int difference = abs(x1 - x2);

  if(y1 - difference <= y2 && y1 + difference >= (y2 + 1))
  {
    return 1;
  }

  return 0;
}
