#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "packing.h"

int main(int argc, char * argv[])
{
  // Check to make sure two options are given
  if(argc != 3)
  {
    printf("Usage: ./proj3 <input_file> <output_file>\n");
    return EXIT_FAILURE;
  }

  // The input and output files provided by the user
  char * input_file = argv[1];
  char * output_file = argv[2];

  Node * Values = Load_File(input_file); // Load the file

  // Check for any errors in the loading of the file
  if(Values == NULL)
  {
    printf("Load_File function execution unsuccessful\n");
    free(Values); // Free the values if there are any errors
    return EXIT_FAILURE;
  }

  clock_t time; // Used to determine the amount of time taken to sort

  time = clock(); // Get the time before performing the packing operation

  Special_Post_Order(Values, Values[0].left);

  Coordinates(Values, Values[0].left);

  time = clock() - time; //Packing time

  Values[0].height = time / CLOCKS_PER_SEC; // Set the height of the first node to the packing time

  int test = Save_File(Values, output_file); // Save the items to the file

  // Check to make sure the saving to the output file was successful
  // Save_File returns a 0 is successful, and a 1 if unsuccessful
  if(test == 1)
  {
    printf("Save_File function execution unsuccessful\n");
    free(Values); // Free the values if there are any errors
    return EXIT_FAILURE;
  }

  Screen_Dump(Values); // Dump the information to the screen

  free(Values); // Free the allocated values

  return EXIT_SUCCESS; // WE DID IT!!!
}
