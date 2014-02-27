#include<stdio.h>
#include<stdlib.h>
#include "pa02.h"

Node * Load_File(char * input_file)
{
  FILE * iptr = fopen(input_file, "r");

  if(iptr == NULL)
  {
    printf("Error opening input file\n");
    return NULL;
  }

  int numbers = 0;
  long temp;

  while(fscanf(iptr, "%li", &temp) == 1)
  {
    numbers++;
  }

  fseek(iptr, 0, SEEK_SET);

  Node * values;

  values = Create_Struct(iptr, numbers);

  Print_Struct(values);

  fclose(iptr);

  return NULL;
}

// Create a structure of the values that are in the input file
Node * Create_Struct(FILE * iptr, int numbers)
{
  Node * values = NULL;
  Node * root = values;

  while(numbers--)
  {
    values = malloc(sizeof(Node));
    
    if(values == NULL)
    {
      printf("Memory allocation failed\n");
      return NULL;
    }

    fscanf(iptr, "%li", &(values -> value));

    values -> next = NULL;
    values = values -> next;
  }

  return root;
}


void Print_Struct(Node * values)
{
  if(values == NULL)
  {
    return;
  }

  Print_Struct(values -> next);
  printf("%li\n", values -> value);
}

