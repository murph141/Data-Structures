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
    temp = Dijkstra(i, data, num) + (1 - data[i].branch);

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
    char a = fgetc(fptr);

    if(a == '\n')
    {
      a = fgetc(fptr);
    }

    if(a == 49)
    {
      data[i].branch = 1;
    }
    else
    {
      data[i].branch = 0;
    }

    data[i].tr = num * (num - 1) + i / num + (i % num) * num;
    data[i].br = data[i].tr + 1;

    data[i].tl = num * (num - 1) + (i % num - 1) * num + i / num;
    data[i].bl = data[i].tl + 1;

    data[i].up = i - num;
    data[i].dn = i + num;

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

    if(i / num == 0)
    {
      data[i].up = -1;
    }
    else if(i / num == (num - 2))
    {
      data[i].dn = -1;
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
    if(data[i].up != -1)
    {
      if(data[data[i].up].branch == 1)
      {
        data[i].upw = 0;
      }
      else
      {
        data[i].upw = num * num;
      }
    }
    else
    {
      data[i].upw = num * num;
    }

    if(data[i].dn != -1)
    {
      if(data[data[i].dn].branch == 1)
      {
        data[i].dnw = 0;
      }
      else
      {
        data[i].dnw = num * num;
      }
    }
    else
    {
      data[i].dnw = num * num;
    }
  }

  for(i = 0; i < (num * (num - 1)); i++)
  {
    //data[i].distance = num * num;
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
    //data[i].distance = num * num;
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

int Dijkstra(int start, Node * arr, int num)
{
  int i, j;

  Heap * PQ = calloc(sizeof(Heap) * (2 * num * (num - 1) - 1), sizeof(Heap));

  int distance[2 * num * (num - 1)];

  int size = 2 * num * (num - 1);

  for(i = 0; i < (2 * num * (num - 1)); i++)
  {
    PQ[i].dist = num * num;
    PQ[i].nn = i;
    distance[i] = num * num;
  }

  int curr = start;

  PQ[curr].dist = 0;

  distance[curr] = 0;

  while(size != 0)
  {
    Check_Dist(arr, PQ, curr);

    for(j = size - 1; j > 0; j--)
    {
      int temp1, temp2;

      temp1 = PQ[j].dist;
      temp2 = PQ[j].nn;

      PQ[j].dist = PQ[0].dist;
      PQ[j].nn = PQ[0].nn;

      PQ[0].nn = temp2;
      PQ[0].dist = temp1;

      Downward_Heapify(PQ, 0, j - 1);
    }

    if(curr == start)
    {
      size--;
    }

    int u = Extract_Min(PQ, size--);

    curr = u;

    if(arr[u].tr != -1)
    {
      if(IsInPQ(arr[u].tr, PQ, size) && (distance[arr[u].tr] > (distance[u] + arr[u].trw)))
      {
        distance[arr[u].tr] = distance[u] + arr[u].trw;
      }
    }

    if(arr[u].tl != -1)
    {
      if(IsInPQ(arr[u].tl, PQ, size) && (distance[arr[u].tl] > (distance[u] + arr[u].tlw)))
      {
        distance[arr[u].tl] = distance[u] + arr[u].tlw;
      }
    }

    if(arr[u].br != -1)
    {
      if(IsInPQ(arr[u].br, PQ, size) && (distance[arr[u].br] > (distance[u] + arr[u].brw)))
      {
        distance[arr[u].br] = distance[u] + arr[u].brw;
      }
    }

    if(arr[u].bl != -1)
    {
      if(IsInPQ(arr[u].bl, PQ, size) && (distance[arr[u].bl] > (distance[u] + arr[u].blw)))
      {
        distance[arr[u].bl] = distance[u] + arr[u].blw;
      }
    }

    if(arr[u].up != -1)
    {
      if(IsInPQ(arr[u].up, PQ, size) && (distance[arr[u].up] > (distance[u] + arr[u].upw)))
      {
        distance[arr[u].up] = distance[u] + arr[u].upw;
      }
    }

    if(arr[u].dn != -1)
    {
      if(IsInPQ(arr[u].dn, PQ, size) && (distance[arr[u].dn] > (distance[u] + arr[u].dnw)))
      {
        distance[arr[u].dn] = distance[u] + arr[u].dnw;
      }
    }
  }

  int k, best = 2 * num;

  for(k = num - 1; k < (num * (num - 1)); k += num)
  {
    if(distance[k] < best)
    {
      best = distance[k];
    }
  }

  free(PQ);

  return best;
}

void Check_Dist(Node * arr, Heap * PQ,  int start)
{
  if(arr[start].tr != -1)
  {
    if(PQ[arr[start].tr].dist > PQ[start].dist + arr[start].trw)
    {
      PQ[arr[start].tr].dist = PQ[start].dist + arr[start].trw;
    }
  }

  if(arr[start].tl != -1)
  {
    if( PQ[arr[start].tl].dist > PQ[start].dist + arr[start].tlw)
    {
      PQ[arr[start].tl].dist = PQ[start].dist + arr[start].tlw;
    }
  }

  if(arr[start].br != -1)
  {
    if( PQ[arr[start].br].dist > PQ[start].dist + arr[start].brw)
    {
      PQ[arr[start].br].dist = PQ[start].dist + arr[start].brw;
    }
  }

  if(arr[start].bl != -1)
  {
    if( PQ[arr[start].bl].dist > PQ[start].dist + arr[start].blw)
    {
      PQ[arr[start].bl].dist = PQ[start].dist + arr[start].blw;
    }
  }

  if(arr[start].up != -1)
  {
    if( PQ[arr[start].up].dist > PQ[start].dist + arr[start].upw)
    {
      PQ[arr[start].up].dist = PQ[start].dist + arr[start].upw;
    }
  }

  if(arr[start].dn != -1)
  {
    if( PQ[arr[start].dn].dist > PQ[start].dist + arr[start].dnw)
    {
      PQ[arr[start].dn].dist = PQ[start].dist + arr[start].dnw;
    }
  }
}

void Downward_Heapify(Heap * arr, int i, int n)
{
  int j;
  int temp = arr[i].dist;
  int temp2 = arr[i].nn;

  while((j = 2 * i + 1) <= n)
  {
    if(j < n && arr[j].dist < arr[j+1].dist)
    {
      j++;
    }

    if(temp >= arr[j].dist)
    {
      break;
    }
    else
    {
      arr[i].dist = arr[j].dist;
      arr[i].nn = arr[j].nn;
      i = j;
    }
  }

  arr[i].dist = temp;
  arr[i].nn = temp2;
}


int Extract_Min(Heap * PQ, int size)
{
  int temp1, temp2;

  temp1 = PQ[0].nn;
  temp2 = PQ[0].dist;

  PQ[0].nn = PQ[size - 1].nn;
  PQ[0].dist = PQ[size - 1].dist;

  PQ[size - 1].nn = temp1;
  PQ[size - 1].dist = temp2;

  //Downward_Heapify(PQ, 0, size - 2);

  int j;

  for(j = size - 2; j > 0; j--)
  {
    temp1 = PQ[j].dist;
    temp2 = PQ[j].nn;

    PQ[j].dist = PQ[0].dist;
    PQ[j].nn = PQ[0].nn;

    PQ[0].nn = temp2;
    PQ[0].dist = temp1;

    Downward_Heapify(PQ, 0, j - 1);
  }

  return PQ[size - 1].nn;
}


int IsInPQ(int nn, Heap * PQ, int size)
{
  int i, check = 0;

  for(i = 0; i < size; i++)
  {
    if(PQ[i].nn == nn)
    {
      check = 1;
      break;
    }
  }

  return check;
}
