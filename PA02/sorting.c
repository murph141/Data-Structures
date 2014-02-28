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

  if(dummy == NULL)
  {
    printf("Memory allocation failed\n");
    return NULL;
  }

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

    if(dummy -> next == NULL)
    {
      printf("Memory allocation failed\n");
      return NULL;
    }

    dummy = dummy -> next;
  }

  dummy -> next = NULL;

  //Print_Struct(root);

  fclose(iptr);

  return root;
}



// Saves a linked list of values to a file
int Save_File(char * output_file, Node * root)
{
  FILE * optr = fopen(output_file, "w");

  if(optr == NULL)
  {
    printf("File opened unsuccesfully\n");
    return -1; //Since the size cannot be less than 0, the program will exit on error-checking in main
  }

  int successful = 0;
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

  fclose(optr);

  return successful; 
}


Node * Shell_Sort(Node * root)
{
  int * gaps = Generate_Sequence(root -> value);

  int i, j, k, h;

  long temp;

  /*
  for(i = 0; i < Number_Of_Elements(Highest_Power(root -> value)); i++)
  {
    printf("gaps[%d] = %d\n", i, gaps[i]);
  }
  */

  int number = root -> value;
  int size = Number_Of_Elements(Highest_Power(number));

  Node * data = root -> next;

  //Print_Struct(data);

  //printf("\n\n");

  for(h = 0; h < size; h++)
  {
    k = gaps[h];

   // printf("k: %d\n", k);

    /*
    for(j = 0; j < number; j += k)
    {
      printf("%d\n", j);
    }
  }
  */
    for(j = k; j < number; j++)
    {
      temp = Traverse(data, j) -> value;

    //  printf("%li %d\n", temp, j);

      i = j;

      while(i >= k && (Traverse(data, i - k) -> value > temp))
      {
        Traverse(data, i) -> value = Traverse(data, i - k) -> value;

        i -= k;
      }

      Traverse(data, i) -> value = temp;

    }
  }

  /*
  for(i = 0; i < size; i++)
  {
    int temp = gaps[i];

    List * data = malloc(sizeof(List) * temp);

    List * head = data;

    for(j = 0; j < temp; j++)
    {
      for(k = j; k < size; k += temp)
      {
        List -> node = malloc(sizeof(Node));
        List -> node -> value = 

  }
  */

  free(gaps);

  return root;
}


Node * Traverse(Node * root, int i)
{
  Node * first = root;
  while(first != NULL && i--)
  {
    first = first -> next;
  }

  return first;
}


int * Generate_Sequence(int size)
{
  int n = Highest_Power(size);
  int num = Number_Of_Elements(n);

  int * array = malloc(sizeof(int) * num);

  int i, j, count = 0;

  /*
  for(i = 0; i <= n; i++)
  {
    for(j = 0; j <= i; j++)
    {
      array[count++] = Calculate_Number(i - j, j);
    }
  }
  */

  for(i = n; i >= 0; i--)
  {
    for(j = i; j >= 0; j--)
    {
      array[count++] = Calculate_Number(i - j, j);
    }
  }

  return array;
}


Node * Create_Node(long value)
{
  Node * values = malloc(sizeof(Node));

  if(values == NULL)
  {
    printf("Memory allocation failed\n");
    return NULL;
  }

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


int Number_Of_Elements(int n)
{
  return ((n + 1) * (n + 2) / 2);
}

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
