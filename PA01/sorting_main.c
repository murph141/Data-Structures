#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "pa01.h"

int main(int argc, char * argv[])
{
  // Check to make sure the correct number of input arguments are provided
  if(argc != 5)
  {
    printf("Usage: ./proj1 <sorting_method> <input_file> <sequence_file> <output_file>\n");
    return EXIT_FAILURE;
  }

  // Set these variables to the input arguments (Make things easier)
  char method = * argv[1];
  char * input_file = argv[2];
  char * sequence_file = argv[3];
  char * output_file = argv[4];

  // Used to store values used in this program
  int Size;
  long * values;
  clock_t t_sort, t_load, t_save, t_seq;

  // Load the file, keeping track of the time it takes to load the file
  t_load = clock();
  values = Load_File(input_file, &Size);
  t_load = clock() - t_load;

  // Check to make sure the files was loaded correctly
  if(values == NULL)
  {
    printf("Error loading the input file\n");
    return EXIT_FAILURE;
  }


  // Print the sequence to a file, keeping track of the time it takes to write to the file
  t_seq = clock();
  int i = Print_Seq(sequence_file, Size);
  t_seq = clock() - t_seq;
  
  // Check to make sure the sequence was correctly output to the file
  if(i == 0)
  {
    printf("Failed to print sequence\n");
    free(values);
    return EXIT_FAILURE;
  }

  // Used to keep track of the number of moves and comparisons in the sorting algorithms
  double N_Comp = 0.0, N_Move = 0.0;


  // Check for the sorting method chosen by the user
  // Keep track of the time it takes to sort the values as well
  t_sort = clock();
  if(method == 'i')
  {
    Shell_Insertion_Sort(values, Size, &N_Comp, &N_Move);
  }
  else if(method == 's')
  {
    Shell_Selection_Sort(values, Size, &N_Comp, &N_Move);
  }
  else
  {
    printf("Sorting method must be either i (Insertion) or s (Selection) sort\n");
    free(values);
    return EXIT_FAILURE;
  }
  t_sort = clock() - t_sort;


  // Save the sorted array to the output file, keeping track of th time it takes as well
  t_save = clock();
  int returned = Save_File(output_file, values, Size);
  t_save = clock() - t_save;

  // Check to make sure that the file was correctly output to
  if (!returned)
  {
    printf("Failed to output values to file\n");
    free(values);
    return EXIT_FAILURE;
  }
  else if(returned != Size)
  {
    printf("Number of values returned not equal to number of values specified\n");
    free(values);
    return EXIT_FAILURE;
  }
  
  // Free the malloced values
  free(values);

  // Display all the required information to the screen
  Screen_Dump(N_Comp, N_Move, (t_save + t_load + t_seq) / CLOCKS_PER_SEC, t_sort);

  // SUCCESS!!!
  return EXIT_SUCCESS;
}

/*
 *
 * TO DO:
 * 
 * Take care of comparisons and moves
 * Free? (Possibly)
 * Clock time (With Screen_Dump fx)
 *
 */
