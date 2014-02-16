#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "pa01.h"

int main(int argc, char * argv[])
{
  if(argc != 5)
  {
    printf("Usage: ./proj1 <sorting_method> <input_file> <sequence_file> <output_file>\n");
    return EXIT_FAILURE;
  }

  char method = * argv[1];
  char * input_file = argv[2];
  char * sequence_file = argv[3];
  //char * output_file = argv[4];

  int Size;
  long * values;

  values = Load_File(input_file, &Size);

  if(values == NULL)
  {
    return EXIT_FAILURE;
  }

  //clock_t initial_time, after_sequence;

  //initial_time = clock();
  // NEED TO FREE AFTER THIS POINT
  int i = Print_Seq(sequence_file, Size);
  
  if(i == 0)
  {
    printf("Failed to print sequence\n");
    free(values);
    return EXIT_FAILURE;
  }


  double N_Comp = 0.0, N_Move = 0.0;

  // Check for the sorting method chosen by the user
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

  free(values);

  return EXIT_SUCCESS;
}