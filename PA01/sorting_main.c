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
  char * output_file = argv[4];

  int Size;
  long * values;
  clock_t t_sort, t_load, t_save, t_seq;

  t_load = clock();
  values = Load_File(input_file, &Size);
  t_load = clock() - t_load;

  if(values == NULL)
  {
    printf("Error loading the input file\n");
    return EXIT_FAILURE;
  }


  // NEED TO FREE AFTER THIS POINT
  t_seq = clock();
  int i = Print_Seq(sequence_file, Size);
  t_seq = clock() - t_seq;
  
  if(i == 0)
  {
    printf("Failed to print sequence\n");
    free(values);
    return EXIT_FAILURE;
  }


  double N_Comp = 0.0, N_Move = 0.0;

  // Check for the sorting method chosen by the user

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

  t_save = clock();
  int returned = Save_File(output_file, values, Size);
  t_save = clock() - t_save;

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
  
  free(values);

  Screen_Dump(N_Comp, N_Move, (t_save + t_load + t_seq) / CLOCKS_PER_SEC, t_sort);
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
