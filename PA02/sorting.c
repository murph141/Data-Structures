#include<stdio.h>
#include<stdlib.h>
#include "pa02.h"

// Loads the input file into a structure
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


  Node * dummy = malloc(sizeof(Node));
  dummy -> value = numbers;
  dummy -> next = NULL;

  Node * root = dummy;

  while(numbers--)
  {
    if(!fscanf(iptr, "%li", &temp))
    {
      printf("Error scanning in the input values\n");
      return NULL;
    }

    dummy -> next = Create_Node(temp);
    dummy = dummy -> next;
  }

  dummy -> next = NULL;

  //Print_Struct(root);

  fclose(iptr);

  return root;
}



Node * Create_Node(long value)
{
  Node * values = malloc(sizeof(Node));

  values -> value = value;

  values -> next = NULL;

  return values;
}


// Prints a linked list
void Print_Struct(Node * values)
{
  if(values == NULL)
  {
    return;
  }

  printf("%li\n", values -> value);
  Print_Struct(values -> next);
}

// Destroys a linked list
void Destroy_Struct(Node * a)
{
  if(!a)
  {
    return;
  }

  Destroy_Struct(a -> next);
  free(a);
}
