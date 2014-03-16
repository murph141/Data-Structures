#include<stdio.h>
#include<stdlib.h>
#include "packing.h"

Node * Load_File(char * input_file)
{
  FILE * fptr = fopen(input_file, "r");
  
  // Check to make sure you have access to the file/it exists
  if(fptr == NULL)
  {
    printf("Error: File opening unsuccessful\n");
    return NULL;
  }

  // Get the number of leaf nodes and the number of nodes
  // Perform preliminary checks to validate the input
  int leaf_nodes;

  if(fscanf(fptr, "%d", &leaf_nodes) != 1)
  {
    printf("Error: Value(s) in file not present\n");
    return NULL;
  }

  int nodes;

  if(fscanf(fptr, "%d", &nodes) != 1)
  {
    printf("Error: Value(s) in file not present\n");
    return NULL;
  }

  if(nodes != (2 * leaf_nodes - 1))
  {
    printf("Error: Number of nodes and leaf nodes don't correlate\n");
    return NULL;
  }

  // End preliminary checks and input validation

  // Implement the tree as an array (Idea taken from Joe and Professor Koh during review session on 3/14)
  Node * arr = malloc(sizeof(Node) * (nodes + 1));

  int i;

  // Hard-coded values for the first array value
  arr[0].left = -1;
  arr[0].right = -1;
  arr[0].parent = -1;
  arr[0].width = 0;
  arr[0].height = 0;

  for(i = 0; i < nodes; i++)
  {
    int node, parent, left, right;
    double height, width;

    if(fscanf(fptr, "%d %d %d %d", &node, &parent, &left, &right) == 4)
    {
      arr[node].parent = parent;

      if(arr[node].parent == -1)
      {
        arr[0].width = node;
      }

      arr[node].left = left;
      arr[node].right = right;
    }

    char ch = fgetc(fptr);
    ch = fgetc(fptr);
    if(ch == '-')
    {
      fscanf(fptr, " %lf %lf", &width, &height);
      arr[node].width = width;
      arr[node].height = height;
    }
    else
    {
      while(ch != '\n' && ch != EOF)
      {
        ch = fgetc(fptr);
      }
      arr[node].width = 0;
      arr[node].height = 0;
    }
  }

  /*
  for(i = 0; i <= nodes; i++)
  {
    printf("%lf %lf\n", arr[i].height, arr[i].width);
  }
  */

  fclose(fptr);

  return arr;
}

Node * Fix_Values(Node * arr)
{
  return arr;
}

void Special_Post_Order(Node * arr, int index)
{
}

void Screen_Dump(Node * arr)
{
  int root = arr[0].width;

  printf("Preorder: ");
  Pre_Order(arr, root);
  printf("\n");

  printf("Inorder: ");
  In_Order(arr, root);
  printf("\n");

  printf("Postorder: ");
  Post_Order(arr, root);
  printf("\n");
}


void Post_Order(Node * arr, int index)
{
  if(index == -1)
  {
    return;
  }

  Post_Order(arr, arr[index].left);

  Post_Order(arr, arr[index].right);

  printf("%d ", index);
}


void Pre_Order(Node * arr, int index)
{
  if(index == -1)
  {
    return;
  }

  printf("%d ", index);

  Pre_Order(arr, arr[index].left);

  Pre_Order(arr, arr[index].right);
}


void In_Order(Node * arr, int index)
{
  if(index == -1)
  {
    return;
  }

  In_Order(arr, arr[index].left);

  printf("%d ", index);

  In_Order(arr, arr[index].right);
}
