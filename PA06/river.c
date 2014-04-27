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


// Loads the file and later creates the graph
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

  int best = Dijkstra(data);

  FreeData(data);

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

  // Calculate distances
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
          data[index].dist[inner] = 2 * data[index].x + 1;
        }
        else if (inner == (nodes - 2))
        {
          data[index].dist[inner] = 2 * (num - 1 - data[index].x) + 1;
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
            int changey = abs(data[data[index].adj[inner]].y - data[index].y);

            data[index].dist[inner] = 2 * (changey - 1);
          }
        }
      }
    }
  }
}


int IsInCone(int x1, int y1, int x2, int y2)
{
  int difference = abs(x1 - x2);

  if(y1 - difference <= y2 && y1 + difference >= y2)
  {
    return 1;
  }

  return 0;
}



int Dijkstra(Node * data)
{
  int index, u, j, distance;
  int nodes = ones + 2; 

  Heap * PQ = calloc(nodes, sizeof(Heap));

  for(index = 0; index < nodes; index++)
  {
    PQ[index].number = index;
    PQ[index].dist = num * num;
  }

  PQ[nodes - 2].dist = 0;

  // Perform downward heapify
  for(j = nodes - 1; j > 0; j--)
  {
    swap(PQ, j, 0);

    Downward_Heapify(PQ, 0, j - 1);
  }
  
  while(nodes > 0)
  {
    u = Extract_Min(PQ, nodes);

    if(u == (ones + 1))
    {
      distance = PQ[0].dist;

      free(PQ);
      return distance;
    }

    nodes--;

    Check_Adjacent(PQ, data, u, nodes);
  }

  free(PQ);
  return -1;
}


int Extract_Min(Heap * PQ, int nodes)
{
  int temp = PQ[0].number;

  swap(PQ, 0, nodes - 1);

  Downward_Heapify(PQ, 0, nodes - 2);

  return temp;
}

void Downward_Heapify(Heap * PQ, int i, int n)
{
  int temp = PQ[i].dist;
  int temp2 = PQ[i].number;

  int j;

  while((j = 2 * i + 1) <= n)
  {
    if(j < n && PQ[j].dist < PQ[j + 1].dist)
    {
      j++;
    }

    if(temp >= PQ[j].dist)
    {
      break;
    }
    else
    {
      swap(PQ, i, j);
      i = j;
    }
  }

  PQ[i].dist = temp;
  PQ[i].number = temp2;
}

void Check_Adjacent(Heap * PQ, Node * data, int u, int nodes)
{
  int i, j, totalnodes = ones + 1;
  int temp, location;

  for(i = 0, j = 0; i < totalnodes; i++, j++)
  {
    if(j == u)
    {
      j++;
    }

    temp = data[u].dist[i];
    
    location = FindPQ(PQ, j, nodes);

    if(PQ[location].dist > PQ[nodes].dist + temp)
    {
      PQ[location].dist = PQ[nodes].dist + temp;
    }
  }

  for(j = nodes - 1; j > 0; j--)
  {
    swap(PQ, j, 0);

    Downward_Heapify(PQ, 0, j - 1);
  }
}


void swap(Heap * h1, int i1, int i2)
{
  int t1 = h1[i1].dist;
  int t2 = h1[i1].number;

  h1[i1].dist = h1[i2].dist;
  h1[i1].number= h1[i2].number;

  h1[i2].dist = t1;
  h1[i2].number = t2;
}

int FindPQ(Heap * PQ, int needle, int total)
{
  int i;

  for(i = 0; i < total; i++)
  {
    if(PQ[i].number == needle)
    {
      return i;
    }
  }
  
  return i;
}


void FreeData(Node * data)
{
  int i;

  for(i = 0; i < (ones + 2); i++)
  {
    free(data[i].adj);
    free(data[i].dist);
  }

  free(data);
}
