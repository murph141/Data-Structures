// Include guard
#ifndef PA01_H
#define PA01_H

// Used for file I/O
long * Load_File(char *, int *);
int Save_File(char *, long *, int);
int Print_Seq(char *, int);

// Used for sorting the data
void Shell_Insertion_Sort(long *, int, double *, double *);
void Shell_Selection_Sort(long *, int, double *, double *);

// Used for file validation
int Validate_Numbers(FILE *);

// Used for output validation
int The_Size(long);

// Used in the sequence generation
int * Generate_Sequence(int);
int Highest_Power(int);
int Number_Of_Elements(int);
int Calculate_Number(int, int);

// Displays the the required in fo to stdin
void Screen_Dump(double, double, double, double);

// Swaps two long values
void Swap(long *, long *);

#endif /* PA01_H */
