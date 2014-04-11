#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "reroot.h"


// Main function (Does everything)
int main(int argc, char * argv[])
{
  // Check for the correct number of arguments
  if(argc != 3)
  {
    printf("Usage: proj4 <input_file> <output_file>\n");
    return EXIT_FAILURE;
  }

  // Save the inputs to variables
  char * input = argv[1];
  char * output = argv[2];

  Node * Tree; // Create the initial tree pointer

  clock_t reroot_time, time; // Used to calculate time

  time = clock(); // Get the current time

  Tree = Load_File(input); // Load the file's inputs into the Tree pointer (Tree)

  // Check for errors
  if(Tree == NULL)
  {
    return EXIT_FAILURE; // We failed
  }

  Special_Post_Order(Tree); // Fix the values

  Coordinates(Tree); // Fix the coordinates

  time = clock() - time; // Get the total time taken

  int success = Save_File(Tree, output); // Save the output into a file (With a return value checking success)

  // Check for success
  if(success == 1)
  {
    destroy_Tree(Tree); // Destroy the tree if an error occured
    return EXIT_FAILURE; // We failed
  }

  double width = Tree -> width; // The best current width is the original width
  double height = Tree -> height; // The best current height is the original height

  reroot_time = clock(); // Get the current time

  Reroot(&width, &height, Tree, 0, 0, Tree -> slice, 'L'); // Call the reroot function on the left side
  Reroot(&width, &height, Tree, 0, 0, Tree -> slice, 'R'); // Call the reroot function on the right side
 
  reroot_time = clock() - reroot_time; // Calculate the total time taken

  Screen_Dump(Tree, width, height, time / CLOCKS_PER_SEC, reroot_time / CLOCKS_PER_SEC); // Dump all the values to the screen

  destroy_Tree(Tree); // Destroy the tree

  return EXIT_SUCCESS; // SUCCESS!!!!
}


// Load the values from the file
Node * Load_File(char * input)
{
  Stack * s = NULL; // Create a stack
  Node * n1, * n2, * n3; // Declare three temp nodes
  double width, height; // Width and height values
  FILE * fptr = fopen(input, "r"); // Open the file for reading

  // Check for file opening errors
  if(fptr == NULL)
  {
    printf("Error: Memory allocation failed.\n");
    return NULL;
  }

  char a = fgetc(fptr); // Get the first character in the file

  // Continue to iterate through the file until we're are the end
  while(a != '\n' && a != EOF)
  {
    // Check for a leaf node
    if(a == '(')
    {
      fscanf(fptr, "%lf, %lf)", &width, &height); // Scan in the new values
      push(&s, Create_Node(width, height, '-')); // Push the node on to the stack
    }
    else
    {
      // We're at a non-leaf node

      n1 = pop(&s); // Pop the first node
      n2 = pop(&s); // Pop the second node

      n3 = Create_Node(0, 0, a); // Create a new node
      n3 -> left = n2; // Assign the left pointer to one of the popped values
      n3 -> right = n1; // Assign the right pointer to one of the popped values

      push(&s, n3); // Push the new node on to the stack
    }

    a = fgetc(fptr); // Get the next character in the file
  }

  n3 = pop(&s); // Pop the last item in the stack (It is your tree)

  fclose(fptr); // Close the file

  return n3; // Return the node
}


// Saves the information to the file
int Save_File(Node * root, char * output)
{
  FILE * fptr = fopen(output, "w"); // Open the file for writing

  // Check for file opening errors
  if(fptr == NULL)
  {
    printf("Error: Save file cannot be opened for writing\n");
    return 1; // 1 signifies an error
  }

  int success = 1;

  Save_File_Helper(fptr, root, &success); // Call the helper file

  if(success == 0)
  {
    return 1; // 1 signifies an error
  }

  return 0; // 0 signifies success
}


// Helps the save file function
void Save_File_Helper(FILE * fptr, Node * root, int * success)
{
  if(root == NULL)
  {
    return;
  }

  Save_File_Helper(fptr, root -> left, success); // Call the helper file recursively
  Save_File_Helper(fptr, root -> right, success); // Call the helper file recursively

  if(root -> slice == '-')
  {
    // We're at a leaf node
    // Print all the stuff and check for errors
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

// Checks if a stack is empty
int isEmpty(Stack * s)
{
  if(s == NULL)
  {
    return 1;
  }

  return 0;
}


// Push an item to the stack
void push(Stack ** s, Node * n)
{
  Stack * s2 = malloc(sizeof(Stack));
  s2 -> next = * s;
  s2 -> item = n;

  *s = s2;
}


// Create a new node
Node * Create_Node(double width, double height, char a)
{
  Node * n = malloc(sizeof(Node)); // Space for a new node

  // Check for memory allocation problems
  if(n == NULL)
  {
    printf("Error: Memory cannot be allocated\n");
    return NULL;
  }

  // Values (Given from the file or default values)
  n -> left = NULL;
  n -> right = NULL;
  n -> width = width;
  n -> height = height;
  n -> x = 0;
  n -> y = 0;
  n -> slice = a;

  return n; // Return the node
}


// Pops an item from the stack
Node * pop(Stack ** s)
{
  // Check if the stack is empty
  if(isEmpty(*s))
  {
    return NULL;
  }

  // Operations to manipulate the stack
  Stack * top = * s;
  Node * n = top -> item;
  * s = top -> next;

  free(top);

  return n; // Return the new node
}


// Destroy the tree
void destroy_Tree(Node * root)
{
  if(root == NULL)
  {
    return;
  }

  // Post-Order traversal
  destroy_Tree(root -> left);
  destroy_Tree(root -> right);

  free(root);
}


// The special post order function from PA03 (With pointers instead of array indicies)
void Special_Post_Order(Node * root)
{
  // Check for NULL children
  if(root -> left == NULL && root -> right == NULL)
  {
    return;
  }

  // Post-Order Traversal
  Special_Post_Order(root -> left);
  Special_Post_Order(root -> right);

  // Perform operations to determine the sizes of the rectangles (See PA03 for more details)
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


// Calculate the coordinates of the tree's nodes
void Coordinates(Node * root)
{
  // Check for a vertical or horizontal slice, and perform operations afterwards
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

  // Pre-Order Traversal
  Coordinates(root -> left);
  Coordinates(root -> right);
}


// Dump all the information to the screen
void Screen_Dump(Node * root, double width, double height, double time, double reroot_time)
{
  // Preorder, Postorder, Inorder traversals
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

  // Iterate over the tree and the second to last node is the given node
  while(temp != NULL)
  {
    temp2 = temp;
    temp = temp -> left;
  }

  // Values from the temporary tree pointer
  printf("\nX-Coordinate: %le\n", temp2 -> x);
  printf("Y-Coordinate: %le\n\n", temp2 -> y);

  // Values from main (Times and sizes)
  printf("Elapsed time: %le", time);
  printf("\n\nBest Width: %le", width);
  printf("\nBest Height: %le", height);
  printf("\n\nElapsed time for re-rooting: %le\n", reroot_time);
}


// Perform a preorder traversal
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


// Perform an inorder traversal
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


// Perform a postorder traversal
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


// Perform the rerooting
void Reroot(double * min_width, double * min_height, Node * root, double ow, double oh, char slice, char direction)
{
  // Check if we're at a leaf node
  if(root -> slice == '-')
  {
    return;
  }

  // Temporary values
  double w, h, width, height;

  // Check if we're calling to the left or right
  if(direction == 'R')
  {
    // Check if our slice is vertical or horizontal (On the side node)
    if(slice == 'V')
    {
      w = root -> left -> width + ow; // Calculate the new width

      // Check if the left or right child has the larger height
      if(oh < root -> left -> height)
      {
        h = root -> left -> height; // Calculate the new height
      }
      else
      {
        h = oh; // Calculate the new height
      }
    }
    else
    {
      h = root -> left -> height + oh; // Calculate the new height

      // Check if the left or right child has the larger width
      if(ow < root -> left -> width)
      {
        w = root -> left -> width; // Calculate the new width
      }
      else
      {
        w = ow; // Calculate the new width
      }
    }

    // Check if our slice is horizontal or vertical (On the root node now)
    if(root -> slice == 'V')
    {
      width = w + root -> right -> width; // Calculate the new width

      // Check if the right or left child has the larger height
      if(root -> right -> height < h)
      {
        height = h; // Calculate the new height
      }
      else
      {
        height = root -> right -> height; // Calculate the new height
      }
    }
    else
    {
      height = h + root -> right -> height; // Calculate the new height

      // Check if the left or right child has the larger width
      if(root -> right -> width < w)
      {
        width = w; // Calculate the new width
      }
      else
      {
        width = root -> right -> width; // Calculate the new width
      }
    }
  }
  else if(direction == 'L')
  {
    // Check if our slice is horizontal or vertical (On the side node now)
    if(slice == 'V')
    {
      w = root -> right -> width + ow; // Calculate the new width

      // Check if the left or right child has the larger width
      if(oh < root -> right -> height)
      {
        h = root -> right -> height; // Calculate the new height
      }
      else
      {
        h = oh; // Calculate the new height
      }
    }
    else
    {
      h = root -> right -> height + oh; // Calculate the new height

      // Check if the left or right child has the larger width
      if(ow < root -> right -> width)
      {
        w = root -> right -> width; // Calculate the new width
      }
      else
      {
        w = ow; // Calculate the new width
      }
    }

    // Check if our slice is horizontal or vertical (On the root node now)
    if(root -> slice == 'V')
    {
      width = w + root -> left -> width; // Calculate the new width

      // Check if the left or right child has the larger width
      if(root -> left -> height < h)
      {
        height = h; // Calculate the new height
      }
      else
      {
        height = root -> left -> height; // Calculate the new height
      }
    }
    else
    {
      height = h + root -> left -> height; // Calculate the new height

      // Check if the left or right child has the larger width
      if(root -> left -> width < w)
      {
        width = w; // Calculate the new width
      }
      else
      {
        width = root -> left -> width; // Calculate the new width
      }
    }
  }

  // Check if the new height and width values are more efficient
  if((width * height) < (*min_width * *min_height))
  {
    *min_width = width;
    *min_height = height;
  }

  // If we came from the right, we have to continue right
  if(direction == 'R')
  {
    Reroot(min_width, min_height, root -> right, w, h, root -> slice, 'R'); // Call the function recursive (Rerooting on the right side)
    Reroot(min_width, min_height, root -> right, w, h, root -> slice, 'L'); // Call the function recursive (Rerooting on the left side)
  }
  // If we came from the left, we have to continue left
  else
  {
    Reroot(min_width, min_height, root -> left, w, h, root -> slice, 'L'); // Call the function recursive (Rerooting on the left side);
    Reroot(min_width, min_height, root -> left, w, h, root -> slice, 'R'); // Call the function recursive (Rerooting on the right side)
  }
}
