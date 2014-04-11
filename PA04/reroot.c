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
  char * output = argv[2];

  Node * Tree;

  Tree = Load_File(input);

  Special_Post_Order(Tree);

  Coordinates(Tree);

  int success = Save_File(Tree, output);

  if(success == 1)
  {
    destroy_Tree(Tree);
    return EXIT_FAILURE;
  }

  double width = Tree -> width;
  double height = Tree -> height;

  Reroot(&width, &height, Tree, 0, 0, Tree -> slice, 'L');
  Reroot(&width, &height, Tree, 0, 0, Tree -> slice, 'R');

  //Reroot(&width, &height, Tree -> left, Tree -> right -> width, Tree -> right -> width, Tree -> slice, 'L');
  //Reroot(&width, &height, Tree -> left, Tree -> right -> width, Tree -> right -> width, Tree -> slice, 'R');

  Screen_Dump(Tree);

  printf("\n%le %le\n", width, height);

  destroy_Tree(Tree);

  return EXIT_SUCCESS;
}

Node * Make_Dummy(Node * root)
{
  Node * n1 = calloc(1, sizeof(Node));
  Node * n2 = calloc(1, sizeof(Node));

  n1 -> slice = '-';
  n2 -> slice = 'V';
  n2 -> left = n1;
  n2 -> right = root;

  return n2;
}

Node * Load_File(char * input)
{
  Stack * s = NULL;
  Node * n1, * n2, * n3;
  double width, height;
  FILE * fptr = fopen(input, "r");

  char a = fgetc(fptr);

  while(a != '\n' && a != EOF)
  {
    if(a == '(')
    {
      fscanf(fptr, "%lf, %lf)", &width, &height);
      push(&s, Create_Node(width, height, '-'));
    }
    else
    {
      n1 = pop(&s);
      n2 = pop(&s);

      n3 = Create_Node(0, 0, a);
      n3 -> left = n2;
      n3 -> right = n1;

      push(&s, n3);
    }

    a = fgetc(fptr);
  }

  n3 = pop(&s);

  fclose(fptr);

  return n3;
}


int Save_File(Node * root, char * output)
{
  FILE * fptr = fopen(output, "w");

  if(fptr == NULL)
  {
    printf("Error: Save file cannot be opened for writing\n");
    return 1;
  }

  int success = 1;

  Save_File_Helper(fptr, root, &success);

  if(success == 0)
  {
    return 1;
  }

  return 0;
}


void Save_File_Helper(FILE * fptr, Node * root, int * success)
{
  if(root == NULL)
  {
    return;
  }

  Save_File_Helper(fptr, root -> left, success);
  Save_File_Helper(fptr, root -> right, success);

  if(root -> slice == '-')
  {
    if(fprintf(fptr, "%le %le %le %le\n", root -> width, root -> height, root -> x, root -> y) < 0)
    {
      printf("Error: Output file unsuccessfully written to\n");
      success = 0;
    }
  }
  else
  {
    return;
  }
}


int isEmpty(Stack * s)
{
  if(s == NULL)
  {
    return 1;
  }

  return 0;
}


void push(Stack ** s, Node * n)
{
  Stack * s2 = malloc(sizeof(Stack));
  s2 -> next = * s;
  s2 -> item = n;

  *s = s2;
}


Node * Create_Node(double width, double height, char a)
{
  Node * n = malloc(sizeof(Node));

  if(n == NULL)
  {
    printf("Error: Memory cannot be allocated\n");
    return NULL;
  }

  n -> left = NULL;
  n -> right = NULL;
  n -> width = width;
  n -> height = height;
  n -> x = 0;
  n -> y = 0;
  n -> slice = a;

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


void destroy_Tree(Node * root)
{
  if(root == NULL)
  {
    return;
  }

  destroy_Tree(root -> left);
  destroy_Tree(root -> right);

  free(root);
}


void Special_Post_Order(Node * root)
{
  if(root -> left == NULL && root -> right == NULL)
  {
    return;
  }

  Special_Post_Order(root -> left);
  Special_Post_Order(root -> right);

  if(root -> width == 0 && root -> left -> width != 0 && root -> right -> width != 0)
  {
    if(root -> slice == 'V')
    {
      root -> width = root -> left -> width + root -> right -> width;

      if(root -> left -> height > root -> right -> height)
      {
        root -> height = root -> left -> height;
      }
      else
      {
        root -> height = root -> right -> height;
      }
    }
    else
    {
      root -> height = root -> left -> height + root -> right -> height;

      if(root -> left -> width > root -> right -> width)
      {
        root -> width = root -> left -> width;
      }
      else
      {
        root -> width = root -> right -> width;
      }
    }
  }
}


void Coordinates(Node * root)
{
  if(root -> slice == 'V')
  {
    root -> right -> x = root -> x + root -> left -> width;
    root -> right -> y = root -> y;

    root -> left -> x = root -> x;
    root -> left -> y = root -> y;
  }
  else if(root -> slice == 'H')
  {
    root -> right -> x = root -> x;
    root -> right -> y = root -> y;

    root -> left -> x = root -> x;
    root -> left -> y = root -> y + root -> right -> height;
  }
  else
  {
    return;
  }

  Coordinates(root -> left);
  Coordinates(root -> right);
}


void Screen_Dump(Node * root)
{
  printf("\nPreorder: ");
  Pre_Order(root);

  printf("\n\nInorder: ");
  In_Order(root);

  printf("\n\nPostorder: ");
  Post_Order(root);

  printf("\n\nWidth: %le\n", root -> width);
  printf("Height: %le\n", root -> height);

  // Used for the X and Y Coordinates
  Node * temp = root, * temp2;

  while(temp != NULL)
  {
    temp2 = temp;
    temp = temp -> left;
  }

  printf("\nX-Coordinate: %le\n", temp2 -> x);
  printf("Y-Coordinate: %le\n\n", temp2 -> y);

  printf("Elapsed time: ");

  printf("\n\nBest Width: ");
  printf("\nBest Height: ");

  printf("\n\nElapsed time: \n");
}


void Pre_Order(Node * root)
{
  if(root == NULL)
  {
    return;
  }

  if(root -> slice == '-')
  {
    printf("(%le, %le)", root -> width, root -> height);
  }
  else
  {
    printf("%c", root -> slice);
  }

  Pre_Order(root -> left);
  Pre_Order(root -> right);
}


void In_Order(Node * root)
{
  if(root == NULL)
  {
    return;
  }

  In_Order(root -> left);

  if(root -> slice == '-')
  {
    printf("(%le, %le)", root -> width, root -> height);
  }
  else
  {
    printf("%c", root -> slice);
  }

  In_Order(root -> right);
}


void Post_Order(Node * root)
{
  if(root == NULL)
  {
    return;
  }

  Post_Order(root -> left);
  Post_Order(root -> right);

  if(root -> slice == '-')
  {
    printf("(%le, %le)", root -> width, root -> height);
  }
  else
  {
    printf("%c", root -> slice);
  }
}

void Reroot(double * min_width, double * min_height, Node * root, double ow, double oh, char slice, char direction)
{
  if(root -> slice == '-')
  {
    return;
  }

  double w, h, width, height;

  if(direction == 'R')
  {
    if(slice == 'V')
    {
      w = root -> left -> width + ow;

      if(oh < root -> left -> height)
      {
        h = root -> left -> height;
      }
      else
      {
        h = oh;
      }
    }
    else
    {
      h = root -> left -> height + oh;

      if(ow < root -> left -> width)
      {
        w = root -> left -> width;
      }
      else
      {
        w = ow;
      }
    }

    if(root -> slice == 'V')
    {
      width = w + root -> right -> width;

      if(root -> right -> height < h)
      {
        height = h;
      }
      else
      {
        height = root -> right -> height;
      }
    }
    else
    {
      height = h + root -> right -> height;

      if(root -> right -> width < w)
      {
        width = w;
      }
      else
      {
        width = root -> right -> width;
      }
    }
  }
  else if(direction == 'L')
  {
    if(slice == 'V')
    {
      w = root -> right -> width + ow;

      if(oh < root -> right -> height)
      {
        h = root -> right -> height;
      }
      else
      {
        h = oh;
      }
    }
    else
    {
      h = root -> right -> height + oh;

      if(ow < root -> right -> width)
      {
        w = root -> right -> width;
      }
      else
      {
        w = ow;
      }
    }

    if(root -> slice == 'V')
    {
      width = w + root -> left -> width;

      if(root -> left -> height < h)
      {
        height = h;
      }
      else
      {
        height = root -> left -> height;
      }
    }
    else
    {
      height = h + root -> left -> height;

      if(root -> left -> width < w)
      {
        width = w;
      }
      else
      {
        width = root -> left -> width;
      }
    }
  }

  if((width * height) < (*min_width * *min_height))
  {
    *min_width = width;
    *min_height = height;
  }

  if(direction == 'R')
  {
    Reroot(min_width, min_height, root -> right, w, h, root -> slice, 'R');
    Reroot(min_width, min_height, root -> right, w, h, root -> slice, 'L');
  }
  else
  {
    Reroot(min_width, min_height, root -> left, w, h, root -> slice, 'L');
    Reroot(min_width, min_height, root -> left, w, h, root -> slice, 'R');
  }
}
