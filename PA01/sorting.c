#include<stdio.h>
#include<stdlib.h>
#include "pa01.h"

//Validates whether the number given in the input file specifies the actual number of input arguments
int Validate_Numbers(FILE * iptr)
{
  int num;
  long temp;

  fscanf(iptr, "%d", &num);

  while(fscanf(iptr, "%li", &temp) == 1)
  {
    // Decrement num for every successful scan
    // num should equal 0 at the end
    num--;
  }

  // Set the file back to the beginning
  fseek(iptr, 0, SEEK_SET);
  return num;
}


// Loads the specified file
// Checks to make sure:
//      The load was successful
//      The number of items equals the number that was specified
//      Fscanf worked correctly
long * Load_File(char * filename, int * Size)
{
  FILE * iptr = fopen(filename, "r");

  // File had an error being opened
  if(iptr == NULL)
  {
    printf("Error opening input file\n");
    return NULL;
  }

  int valid = Validate_Numbers(iptr);

  // Check if the number of items scanned matches the number of items specified
  if(valid)
  {
    printf("Number of items scanned does not equal number of items specified\n");
    fclose(iptr);
    return NULL;
  }

  // Scan the first value in as the size
  fscanf(iptr, "%d", Size);

  // Allocate space for the array of longs
  long * values = malloc(sizeof(long) * (* Size));

  // Counter variable
  int i;

  for(i = 0; i < (* Size); i++)
  {
    // Check for a successful scan
    if(fscanf(iptr, "%li", values + i) != 1)
    {
      return NULL;
    }
  }

  // Close the file
  fclose(iptr);
  
  // Return the array of scanned values
  return values;
}


// Saves the sorted sequence to a file (Specified by the user)
// Checks to make sure:
//      The file was opened successfully
//      Fprintf was successfull

int Save_File(char * filename, long * array, int Size)
{
  FILE * optr = fopen(filename, "w");

  // Check if the file access was successful
  if (optr == NULL)
  {
    return 0;
  }

  // Save the size into the file first
  fprintf(optr, "%d\n", Size);

  // Counter variables
  int i = 0, returned = 0;

  for(; i < Size; i++)
  {
    // Print each value in the sorted array to the output file
    // Check if the values are being output successfully
    if(fprintf(optr, "%li\n", array[i]) == (The_Size(array[i]) + 1))
    {
      returned++;
    }
  }

  fclose(optr);

  // Return the number of values that were successfully written to the output file
  return returned;
}


// Get the size of the element give plus one
// Used in conjunction with fprintf to validate input
int The_Size(long num)
{
  // If the number equals 0, do this to avoid errors
  if(!num)
  {
    return 1;
  }

  // Counter variable
  int i = 0;

  if(num < 0)
  {
    num = 0 - num;
    i++;
  }

  // While the number is non-zero
  while(num > 0)
  {
    num /= 10;
    i++;
  }

  // Return the length of the value
  // Used for input validation
  return i;
}



// Prints the pyramid sequence to a given file
// Checks to make sure:
//        The file was opened successfully
int Print_Seq(char * filename, int size)
{
  FILE * sptr = fopen(filename, "w");

  // Check if the file access was successful or not
  if(sptr == NULL)
  {
    return 0;
  }

  // Find the highest power of three that is less than or equal to the size of the array of longs
  int n = Highest_Power(size);

  // If n is less than zero, highest_power encountered an error
  if(n < 0)
  {
    return 0;
  }

  // The number of elements that will be in the pyramid
  int number = Number_Of_Elements(n);

  // Print the number of elements to the file first
  fprintf(sptr, "%d\n", number);

  // Counter variables
  int i, j; 

  // Iterate through the pyramid with two for loops
  for(i = 0; i <= n; i++)
  {
    for(j = 0; j <= i; j++)
    {
      // Print the value to the file
      fprintf(sptr, "%d\n", Calculate_Number(i -j, j));
    }
  }

  fclose(sptr);

  // Return the number of values that are in the pyramid
  return number;
}


// Computes the highest power of three that is less than or equal to the size of the array
// Self explanatory
int Highest_Power(int size)
{
  int n = 0;

  while (size > 0)
  {
    size /= 3;
    n++;
  }

  // Return n - 1 because I assumed the top of the pyramid would be at level 0
  return (n - 1);
}


// Returns the number of elements that will be in the pyramid used for sorting
int Number_Of_Elements(int n)
{
  // Using (first + last) * (number of elements) / 2
  return ((n + 1) * (n + 2) / 2);
}


// Calculates the number in the pyramid given a row and column
int Calculate_Number(int i, int j)
{
  int number = 1;

  // Multiply by the specified number of twos
  while(i--)
  {
    number *= 2;
  }

  // Multiply by the specified number of threes
  while(j--)
  {
    number *= 3;
  }

  // Return the number in the pyramid
  return number;
}


// Generates the sequence of the pyramid
int * Generate_Sequence(int size)
{
  // Set n equal to the row that you are on in the pyramid
  int n = Highest_Power(size);

  // Check if n returned an error
  if(n < 0)
  {
    return NULL;
  }

  // The number of elements in the pyramid
  int number = Number_Of_Elements(n);

  // Allocate space for the sequence
  int * sequence = malloc(sizeof(int) * number);

  // Counter variables
  int i, j, count = 0; 

  // Iterative through the sequence and place the values into an array
  for(i = 0; i <= n; i++)
  {
    for(j = 0; j <= i; j++)
    {
      sequence[count++] = Calculate_Number(i -j, j);
    }
  }

  // Return the generated array
  return sequence;
}


// Uses shell sort with an inner insertion sort to sort a given array of longs
// Some code was taken/influenced from the ECE 368 Notes on Shell Sort
void Shell_Insertion_Sort(long * array, int size, double * N_Comp, double * N_Move)
{
  // Generate the pyramid sequence
  int * sequence = Generate_Sequence(size);

  // The number of elements in the pyramid
  int number = Number_Of_Elements(Highest_Power(size));

  // Counter variables
  int h, i, j, k;

  // A temp variable to store an array element
  long temp;

  // First for loop is used to count down so that the elements of the sequence are in reverse order
  // I started the sequence from the top so this loop reverses the sequence essentially
  for(h = number - 1; h >= 0; h--)
  {
    // Set k equal to the current sequence element being referenced
    k = sequence[h];

    // Iterate through the sub arrays
    for(j = k; j < size; j++)
    {
      // Temporarily store the array element
      temp = array[j];

      // This counts as a move
      (* N_Move)++;

      // Set i equal to the current counter variable
      i = j;

      // Insertion sort
      while(i >= k && array[i - k] > temp)
      {
        // Swap the value
        array[i] = array[i - k];
        i -= k;

        // This counts as two compares
        (* N_Comp) += 2;

        // This counts as a move
        (* N_Move)++;
      }

      // Swap the value, continued from the while lop
      array[i] = temp;
      
      // This counts as a move
      (* N_Move)++;
    }
  }

  // Make sure to free the malloced sequence from Generate_Sequence
  free(sequence);
}


// Uses shell sort with an inner selection sort to sort a given array of longs
void Shell_Selection_Sort(long * array, int size, double * N_Comp, double * N_Move)
{
  // Generate the pyramid sequence
  int * sequence = Generate_Sequence(size);

  // The number of elements in the pyramid
  int number = Number_Of_Elements(Highest_Power(size));

  // Counter variables
  int h, i, j, k;

  // First for loop is used to count down so that the elements of the sequence are in reverse order
  // I started the sequence from the top of the pyramid so this loop reverses the sequence essentially
  for(h = number - 1; h >=0; h--)
  {
    // Set k equal to the current sequence element being referenced
    k = sequence[h];

    // Perform selection sort 
    for(j = 0; j < size - 1; j++)
    {
      // k is the gap values so that is being it is being added on to i
      for(i = j + k; i < size; i += k)
      {
        if(array[i] < array[j])
        {
          // Swap the values
          Swap(&array[i], &array[j]);
          
          // This counts as a compare
          (* N_Comp)++;

          // This counts as three moves
          (* N_Move) += 3;
        }
      }
    }
  }

  // Make sure to free the malloced sequence from Generate_Sequence
  free(sequence);
}


// Displays all the required info to stdin
void Screen_Dump(double N_Comp, double N_Move, double IO_Time, double Sorting_Time)
{
  // Dump the required information to stdin

  printf("Number of comparisons: %le\n", N_Comp);
  printf("Number of moves: %le\n", N_Move);
  printf("I/O time: %le\n", IO_Time);
  printf("Sorting time: %le\n", Sorting_Time);
}


// Swaps two long values
void Swap(long * a, long * b)
{
  // Perform a swap, simple enough
  
  long temp = * a;
  * a = * b;
  * b = temp;
}
