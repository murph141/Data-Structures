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
        arr[0].parent = node;
      }

      arr[node].left = left;
      arr[node].right = right;
      arr[node].x = 0;
      arr[node].y = 0;
    }

    char ch = fgetc(fptr);
    ch = fgetc(fptr);
    if(ch == '-')
    {
      fscanf(fptr, " %lf %lf", &width, &height);
      arr[node].width = width;
      arr[node].height = height;
      arr[node].slice = '-';
    }
    else
    {
      arr[node].slice = ch;

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
  if(index == -1)
  {
    return;
  }

  Special_Post_Order(arr, arr[index].left);
  Special_Post_Order(arr, arr[index].right);

  if(arr[index].width == 0 && arr[arr[index].left].width != 0 && arr[arr[index].right].width != 0)
  {
    if(arr[index].slice == 'V')
    {
      arr[index].width = arr[arr[index].left].width + arr[arr[index].right].width;

      if(arr[arr[index].left].height > arr[arr[index].right].height)
      {
        arr[index].height = arr[arr[index].left].height;
      }
      else
      {
        arr[index].height = arr[arr[index].right].height;
      }
    }
    else
    {
      arr[index].height = arr[arr[index].left].height + arr[arr[index].right].height;

      if(arr[arr[index].left].width > arr[arr[index].right].width)
      {
        arr[index].width = arr[arr[index].left].width;
      }
      else
      {
        arr[index].width = arr[arr[index].right].width;
      }
    }
    printf("%d %lf %lf %c\n", index, arr[index].height, arr[index].width, arr[index].slice);
    return;
  }
}

void Screen_Dump(Node * arr)
{
  int root = arr[0].parent;

  printf("Preorder: ");
  Pre_Order(arr, root);
  printf("\n");

  printf("Inorder: ");
  In_Order(arr, root);
  printf("\n");

  printf("Postorder: ");
  Post_Order(arr, root);
  printf("\n");

  printf("Width: %le\n", arr[root].width);
  printf("Height: %le\n", arr[root].height);
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

int Save_File(Node * arr, char * output_file)
{
  FILE * fptr = fopen(output_file, "w");

  if(fptr == NULL)
  {
    printf("Error: File opening unsuccessful\n");
    return 1;
  }

  if(fprintf(fptr, "%d\n", (arr[0].parent + 1) / 2) < 0)
  {
    printf("Error: Outputting to file unsuccessful\n");
    return 1;
  }

  int i;


  for(i = 1; i <= ((arr[0].parent + 1) / 2); i++)
  {
    if(fprintf(fptr, "%d %le %le %le %le\n", i, arr[i].width, arr[i].height, arr[i].x, arr[i].y) < 0)
    {
      printf("Error Outputting to file unsuccessfu;\n");
      return 1;
    }
  }

  return 0;
}


int Deepest_Node(Node * arr, int index)
{
  while(arr[index].right != -1 && arr[index].left != -1)
  {
    if(arr[index].slice == 'V')
    {
      index = arr[index].left;
    }
    else
    {
      index = arr[index].right;
    }
  }
  
  return index;
}


/*
void Coordinates(Node * arr)
{
  int index = arr[0].right;
  int temp;

  while(arr[index].parent != -1)
  {
    if(arr[arr[index].parent].slice == 'V')
    {
      if(arr[arr[index].parent].left == index)
      {
        arr[arr[arr[index].parent].right].x += arr[index].width;
      }
      else
      {
        arr[index].x += arr[arr[arr[index].parent].left].width;
      }
    }
    else
    {
      if(arr[arr[index].parent].left == index)
      {
        arr[index].y += arr[arr[arr[index].parent].right].height;
      }
      else
      {
        arr[arr[arr[index].parent].left].y += arr[index].height;
      }
    }
    index = arr[index].parent;
  }
}
*/
void Coordinates(Node * arr)
{
}
