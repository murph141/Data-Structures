#include<stdio.h>
#include<stdlib.h>
#include "pa02.h"


// Loads the input file into a structure
Node * Load_File(char * input_file)
{
  FILE * iptr = fopen(input_file, "r");

  // Check for file opening errors
  if(iptr == NULL)
  {
    printf("Error opening input file\n");
    return NULL;
  }

  int numbers = 0;
  long temp; // Temp variable used to count the number of items in the input file

  while(fscanf(iptr, "%li", &temp) == 1)
  {
    numbers++;
  }

  // Set the file to the beginning
  fseek(iptr, 0, SEEK_SET);

  Node * dummy = malloc(sizeof(Node));

  // Check for memory allocation errors
  if(dummy == NULL)
  {
    printf("Memory allocation failed\n");
    return NULL;
  }

  // Create a dummy node that contains the number of items in the linked list that follows (Very useful, thanks for the idea Professor Koh)
  dummy -> value = numbers;
  dummy -> next = NULL;

  Node * root = NULL, * prev = NULL;

  // Create a linked list in reverse order (More efficient)
  while(numbers--)
  {
    // Make sure the item in scanned
    if(!fscanf(iptr, "%li", &temp))
    {
      printf("Error scanning in the input values\n");
      return NULL;
    }

    root = Create_Node(temp);

    if(root == NULL)
    {
      root -> next = NULL;
    }
    else
    {
      root -> next = prev;
    }

    prev = root;
  }

  // Place the dummy node at the front of the linked lists
  dummy -> next = root;

  // Close the file
  fclose(iptr);

  // Return the linked list with the dummy node at the front
  return dummy;
}

// Saves a linked list of values to a file
int Save_File(char * output_file, Node * root)
{
  FILE * optr = fopen(output_file, "w");

  // Check for file I/O errors
  if(optr == NULL)
  {
    printf("File opened unsuccesfully\n");
    return -1; //Since the size cannot be less than 0, the program will exit on error-checking in main
  }

  int successful = 0; // The number of successful file writes
  long number = root -> value; // Use the number stored in the dummy 

  root = root -> next; // Bypass the dummy

  while(number--)
  {
    if(fprintf(optr, "%li\n", root -> value) > 0)
    {
      successful++;
    }
    root = root -> next;
  }

  // Close the file
  fclose(optr);

  return successful; // No need to check successful against the actual number here, it is done it main
}

// Does the bulk of the sorting of the linked list
Node * Shell_Sort(Node * root)
{
  // Create an array of the gaps
  int * gaps = Generate_Sequence(root -> value);

  // Something went wrong!
  if(gaps == NULL)
  {
    return NULL;
  }

  // The following code is extrememly similar to the code I used for PA01


  // inner - the inner loop counter
  // outer - the outer loop counter
  // gap - stores the value of the current gap (Descending order)
  // gap_ind - used to track the index of the array the holds the gap values
  int inner, outer, gap, gap_ind;

  // Stores a temporary linked list value
  long temp;

  int number = root -> value; // number is equal to the size of the linked list
  int size = Number_Of_Elements(Highest_Power(number)); // size is the size of the sequence

  Node * data = root -> next; // Bypass the dummy header (It dosen't need to be sorted)

  // Iterate through the gaps
  for(gap_ind = 0; gap_ind < size; gap_ind++)
  {
    //The current gap
    gap = gaps[gap_ind];

    //Outer loop, iterate through the numbers starting at gap
    for(outer = gap; outer < number; outer++)
    {
      //Temp is equal to the value of the value of the loop counter
      temp = Traverse(data, outer) -> value;

      // Set the inner loop variable equal to the outer loop variable
      inner = outer;

      // While inner is still larger than gap AND the value at inner loop counter - gap is greater than the temporary linked list value
      while(inner >= gap && (Traverse(data, inner - gap) -> value > temp))
      {
        // The value are location inner in the linked list is equal to the value at inner - gap
        Traverse(data, inner) -> value = Traverse(data, inner - gap) -> value;

        // Decrement inner by the gap value
        inner -= gap;
      }

      // The value at position inner in the linked list is equal to the temporary value
      Traverse(data, inner) -> value = temp;
    }
  }

  // Free the sequence
  free(gaps);

  // Return root, dummy is part of this structure, the next node of root and on were sorted, but not root
  return root;
}

// Used to traverse a linked list given its root and the number of times to traverse it
Node * Traverse(Node * root, int i)
{
  // Store the location of the root
  Node * first = root;

  while(first != NULL && i--)
  {
    first = first -> next;
  }

  return first;
}

// Generates the pyramid sequence
int * Generate_Sequence(int size)
{
  // The number of columns in the pyramid (0 is the intial index)
  int n = Highest_Power(size);

  // The number of elements in the sequence
  int num = Number_Of_Elements(n);

  // Allocate space for the sequence
  int * array = malloc(sizeof(int) * num);

  // Check for memory errors
  if(array == NULL)
  {
    printf("Memory allocation failed\n");
    return NULL;
  }

  // Counter variables
  int i, j, count = 0;

  // Fill the sequence, as verbatim to the code for PA01
  for(i = n; i >= 0; i--)
  {
    for(j = i; j >= 0; j--)
    {
      array[count++] = Calculate_Number(i - j, j);
    }
  }

  // Return the sequence
  return array;
}

// Create a linked list node
Node * Create_Node(long value)
{
  // Allocate space
  Node * values = malloc(sizeof(Node));

  // Check for allocation errors
  if(values == NULL)
  {
    printf("Memory allocation failed\n");
    return NULL;
  }

  // Input the value (Very confusing line, lots of value(s))
  values -> value = value;

  values -> next = NULL;

  // Return the link
  return values;
}

// Prints a linked list
void Print_Struct(Node * values)
{
  if(values == NULL)
  {
    return;
  }

  // Print, then move on
  printf("%li\n", values -> value);
  Print_Struct(values -> next);
}

// Destroys a linked list
void Destroy_Struct(Node * a)
{
  // Check for null
  if(a == NULL)
  {
    return;
  }

  // Call next
  Destroy_Struct(a -> next);
  free(a);
}

// Determines the number of elements in the sequence, same as PA01
int Number_Of_Elements(int n)
{
  return ((n + 1) * (n + 2) / 2);
}

// Returns the highest power in the sequence, same as PA01
int Highest_Power(int size)
{
  int n = 0;

  while(size > 0)
  {
    size /= 3;
    n++;
  }

  return (n - 1);
}

// Calculates the number in the sequence given a row and column, same as PA01
int Calculate_Number(int i, int j)
{
  int number = 1;

  while(i--)
  {
    number *= 2;
  }

  while(j--)
  {
    number *= 3;
  }

  return number;
}

// Prints the I/O and sorting times to the stdout
void Screen_Dump(double io, double sort)
{
  printf("I/O time: %le\n", io);
  printf("Sorting time: %le\n", sort);
}
