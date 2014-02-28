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
  
  // Input and output files from the users input
  char * input_file = argv[1];
  char * output_file = argv[2];

  // Used for sorting and I/O time
  clock_t t_io, t_io2, t_sort;

  t_io = clock();
  Node * values = Load_File(input_file); // Load the values
  t_io = clock() - t_io;

  // Check for errors
  if(!values)
  {
    printf("Error: File loaded unsuccessfully\n");
    return EXIT_FAILURE;
  }

  t_sort = clock();
  values = Shell_Sort(values); // Sort the values
  t_sort = clock() - t_sort;

  // Check for errors
  if(values == NULL)
  {
    printf("Error: Shell sort unsuccessful\n");
    return EXIT_FAILURE;
  }

  t_io2 = clock();
  int successful = Save_File(output_file, values); // Save the values
  t_io2 = clock() - t_io2;

  // Check for errors
  if(successful != values -> value)
  {
    printf("Error: Values in output file and input file differ\n");
    return EXIT_FAILURE;
  }

  // Free the values
  Destroy_Struct(values);

  // Dump all the info the screen
  Screen_Dump((t_io + t_io2) / CLOCKS_PER_SEC, t_sort / CLOCKS_PER_SEC);

  return EXIT_SUCCESS; // WE DID IT
}
