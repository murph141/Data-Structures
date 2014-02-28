#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "pa02.h"

int main(int argc, char * argv[])
{
  if(argc != 3)
  {
    printf("\nUsage: ./proj2 <input_file> <output_file>\n\n");
    return EXIT_FAILURE;
  }
  
  char * input_file = argv[1];
  char * output_file = argv[2];
  clock_t t_io, t_io2, t_sort;

  t_io = clock();
  Node * values = Load_File(input_file);
  t_io = clock() - t_io;

  if(!values)
  {
    printf("Error: File loaded unsuccessfully\n");
    return EXIT_FAILURE;
  }

  t_sort = clock();
  values = Shell_Sort(values);
  t_sort = clock() - t_sort;

  if(values == NULL)
  {
    printf("Error: Shell sort unsuccessful\n");
    return EXIT_FAILURE;
  }

  t_io2 = clock();
  int successful = Save_File(output_file, values);
  t_io2 = clock() - t_io2;

  if(successful != values -> value)
  {
    printf("Error: Values in output file and input file differ\n");
    return EXIT_FAILURE;
  }

  Destroy_Struct(values);

  Screen_Dump((t_io + t_io2) / CLOCKS_PER_SEC, t_sort / CLOCKS_PER_SEC);
  return EXIT_SUCCESS;
}


/*
 *
 * TODO:
 *
 * I/O Time
 * Sorting Time
 * Free?
 * Make sorting faster!!!
 * Write-Up
 *
 */
