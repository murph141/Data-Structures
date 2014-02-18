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
    num--;
  }

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

  if(iptr == NULL)
  {
    printf("Error opening input file\n");
    return NULL;
  }

  int valid = Validate_Numbers(iptr);

  if(valid)
  {
    printf("Number of items scanned does not equal number of items specified\n");
    fclose(iptr);
    return NULL;
  }

  fscanf(iptr, "%d", Size);

  long * values = malloc(sizeof(long) * (* Size));

  int i;

  for(i = 0; i < (* Size); i++)
  {
    if(fscanf(iptr, "%li", values + i) != 1)
    {
      return NULL;
    }
  }

  fclose(iptr);
  return values;
}



// Saves the sorted sequence to a file (Specified by the user)
// Checks to make sure:
//      The file was opened successfully
//      Fprintf was successfull

int Save_File(char * filename, long * array, int Size)
{
  FILE * optr = fopen(filename, "w");

  if (optr == NULL)
  {
    return 0;
  }

  fprintf(optr, "%d\n", Size);

  int i = 0, returned = 0;

  for(; i < Size; i++)
  {
    if(fprintf(optr, "%li\n", array[i]) == (The_Size(array[i]) + 1))
    {
      returned++;
    }
  }

  fclose(optr);

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

  int i = 0;

  while(num > 0)
  {
    num /= 10;
    i++;
  }

  return i;
}



// Prints the pyramid sequence to a given file
// Checks to make sure:
//        The file was opened successfully

int Print_Seq(char * filename, int size)
{
  FILE * sptr = fopen(filename, "w");

  if(sptr == NULL)
  {
    return 0;
  }

  int n = Highest_Power(size);

  if(n < 0)
  {
    return 0;
  }

  int number = Number_Of_Elements(n);

  fprintf(sptr, "%d\n", number);

  int i, j; 

  for(i = 0; i <= n; i++)
  {
    for(j = 0; j <= i; j++)
    {
      fprintf(sptr, "%d\n", Calculate_Number(i -j, j));
    }
  }

  fclose(sptr);

  return number;
}



// Computes the highest power of three that is less than or equal to the size of the array
int Highest_Power(int size)
{
  int n = 0;
  while (size > 0)
  {
    size /= 3;
    n++;
  }

  return (n - 1);
}



// Returns the number of elements that will be in the pyramid used for sorting
int Number_Of_Elements(int n)
{
  return ((n + 1) * (n + 2) / 2);
}



// Calculates the number in the pyramid given a row and column
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




// Generates the sequence of the pyramid
int * Generate_Sequence(int size)
{
  int n = Highest_Power(size);

  if(n < 0)
  {
    return NULL;
  }

  int number = Number_Of_Elements(n);

  int * sequence = malloc(sizeof(int) * number);

  int i, j, count = 0; 

  for(i = 0; i <= n; i++)
  {
    for(j = 0; j <= i; j++)
    {
      sequence[count++] = Calculate_Number(i -j, j);
    }
  }

  return sequence;
}



// Uses shell sort with an inner insertion sort to sort a given array of longs
void Shell_Insertion_Sort(long * array, int size, double * N_Comp, double * N_Move)
{
  int * sequence = Generate_Sequence(size);

  int number = Number_Of_Elements(Highest_Power(size));

  int h, i, j, k;

  long temp;

  for(h = number - 1; h >= 0; h--)
  {
    k = sequence[h];

    for(j = k; j < size; j++)
    {
      temp = array[j];
      (* N_Move)++;

      i = j;

      while(i >= k && array[i - k] > temp)
      {
        array[i] = array[i - k];
        i -= k;
        (* N_Comp) += 2;
        (* N_Move)++;
      }

      array[i] = temp;
      (* N_Move)++;
    }
  }

  free(sequence);
}



// Uses shell sort with an inner selection sort to sort a given array of longs
void Shell_Selection_Sort(long * array, int size, double * N_Comp, double * N_Move)
{
  int * sequence = Generate_Sequence(size);

  int number = Number_Of_Elements(Highest_Power(size));

  int h, i, j, k;

  for(h = number - 1; h >=0; h--)
  {
    k = sequence[h];

    for(j = 0; j < size - 1; j++)
    {
      for(i = j + k; i < size; i += k)
      {
        if(array[i] < array[j])
        {
          Swap(&array[i], &array[j]);
          (* N_Comp)++;
          (* N_Move) += 3;
        }
      }
    }
  }

  free(sequence);
}



// Displays all the required info to stdin
void Screen_Dump(double N_Comp, double N_Move, double IO_Time, double Sorting_Time)
{
  printf("Number of comparisons: %le\n", N_Comp);
  printf("Number of moves: %le\n", N_Move);
  printf("I/O time: %le\n", IO_Time);
  printf("Sorting time: %le\n", Sorting_Time);
}



// Swaps two long values
void Swap(long * a, long * b)
{
  long temp = * a;
  * a = * b;
  * b = temp;
}
