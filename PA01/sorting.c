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
    fscanf(iptr, "%li", values + i);
  }

  fclose(iptr);
  return values;
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
  //int triangle[number];

  int i, j; 
  //int count = 0;

  for(i = 0; i <= n; i++)
  {
    for(j = 0; j <= i; j++)
    {
      fprintf(sptr, "%d\n", Calculate_Number(i -j, j));
      //triangle[count++] = Calculate_Number(i - j, j);
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
