#include<stdio.h>
#include<stdlib.h>
#include "pa01.h"

//Validates whether the number given in the input file specifies
//the actual number of input arguments
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



int The_Size(long num)
{
  int i = 0;

  while(num > 0)
  {
    num /= 10;
    i++;
  }

  return i;
}






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



int Number_Of_Elements(int n)
{
  return ((n + 1) * (n + 2) / 2);
}



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

      i = j;

      while(i >= k && array[i - k] > temp)
      {
        (* N_Comp) += 2;
        array[i] = array[i - k];
        i -= k;
        ( * N_Move)
      }

      array[i] = temp;
    }
  }


  free(sequence);
}




void Shell_Selection_Sort(long * array, int size, double * N_Comp, double * N_Move)
{
  int * sequence = Generate_Sequence(size);

  int number = Number_Of_Elements(Highest_Power(size));
  
  int h, i;
  //long temp;

  for(h = number - 1; h>= 0; h--)
  {
    for(i = h; i < size; i++)
    {
      //temp = array[i];
      //printf("%d %li\n", i, temp);
      int test;

      for(test = 0; test < i; test++)
      {
        printf("array[%d] = %li\n", test, array[test]);
      }
    }
  }

  free(sequence);
}




//May need to change this functions input variables (clock_t may be incorrect)
void Screen_Dump(double N_Comp, double N_Move, double IO_Time, double Sorting_Time)
{
  printf("Number of comparisons: %le\n", N_Comp);
  printf("Number of moves: %le\n", N_Move);
  printf("I/O time: %le\n", IO_Time);
  printf("Sorting time: %le\n", Sorting_Time);
}


void swap(long * a, long * b)
{
  long temp = * a;
  * a = * b;
  * b = temp;
}


long Find_Max(long * array, int size)
{
  int i = 0;
  long min = array[0];

  for(; i < size; i++)
  {
    if(array[i] < min)
    {
      min = array[i];
    }
  }

  return min;
}
