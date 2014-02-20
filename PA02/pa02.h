// Include guard
#ifndef PA02_H
#define PA02_H

// Node structure
typedef struct node {
  long value;
  struct node * next;
} Node;

// List structure
typedef struct list {
  Node * node;
  struct list * next;
} List;

// Used for file I/O
Node * Load_File(char *);
int Save_File(char *, Node *);

// Used for sorting the data
Node * Shell_Sort(Node *);

// May not need these functions

/*
int Validate_Numbers(FILE *);
int Print_Seq(char *, int);
int The_Size(long);
int * Generate_Sequence(int);
int Highest_Power(int);
int Number_Of_Elements(int);
int Calculate_Number(int, int);
void Screen_Dump(double, double, double, double);
void Swap(long *, long *);
*/

#endif /* PA02_H */
