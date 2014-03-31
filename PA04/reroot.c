#include<stdio.h>
#include<stdlib.h>
#include "reroot.h"

int main(int argc, char * argv[])
{
  if(argc != 3)
  {
    printf("Usage: proj4 <input_file> <output_file>\n");
    return EXIT_FAILURE;
  }

  char * input = argv[1];

  Node * Tree;

  Tree = Load_File(input);

  Tree -> left = NULL;

  return EXIT_SUCCESS;
}

Node * Load_File(char * input)
{
  Stack * s = NULL;
  Node * n1, * n2, * n3;
  double width, height;
  FILE * fptr = fopen(input, "r");

  char a = fgetc(fptr);

  while(a != '\n')
  {
    if(a == '(')
    {
      fscanf(fptr, "%lf, %lf)", &width, &height);
      s = push(s, Create_Node(width, height));
    }
    else
    {
      n1 = pop(&s);
      n2 = pop(&s);

      n3 = Create_Node(0, 0);
      n3 -> left = n2;
      n3 -> right = n1;

      push(s, n3);
    }

    a = fgetc(fptr);
  }

  n3 = pop(&s);

  fclose(fptr);

  return n3;
}

int isEmpty(Stack * s)
{
  if(s == NULL)
  {
    return 1;
  }

  return 0;
}

Stack * push(Stack * s, Node * n)
{
  Stack * s2 = malloc(sizeof(Stack));
  s2 -> next = s;
  s2 -> item = n;

  return s2;
}

Node * Create_Node(double width, double height)
{
  Node * n = malloc(sizeof(Node));

  n -> left = NULL;
  n -> right = NULL;
  n -> width = width;
  n -> height = height;
  n -> x = 0;
  n -> y = 0;

  return n;
}

Node * pop(Stack ** s)
{
  if(isEmpty(*s))
  {
    return NULL;
  }

  Stack * top = * s;
  Node * n = top -> item;

  * s = top -> next;

  free(top);

  return n;
}
