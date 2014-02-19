#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "pa01.h"

//Validates whether the number given in the input file specifies
//the actual number of input arguments
int validate_numbers(FILE * iptr)
{
  long num;
  long temp;

  fscanf(iptr, "%li", &num);

  while(fscanf(iptr, "%li", &temp) == 1)
  {
    num--;
  }

  fseek(iptr, 0, SEEK_SET);
  return num;
}
