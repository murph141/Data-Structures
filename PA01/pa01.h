#ifndef PA01_H
#define PA01_H

long * Load_File(char *, int *);
int Save_File(char *, long *, int);

void Shell_Insertion_Sort(long *, int, double *, double *);
void Shell_Selection_Sort(long *, int, double *, double *);

int Print_Seq(char *, int);

int Validate_Numbers(FILE *);
int Highest_Power(int);
int Number_Of_Elements(int);
int Calculate_Number(int, int);

int * Generate_Sequence(int);
int The_Size(long);

void Screen_Dump(double, double, double, double);
void swap(long *, long *);

long Find_Max(long *, int);
#endif /* PA01_H */
