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

//Creates a linked list node 
Node * Create_Node(long);

// Miscellaneous linked list tasks
void Print_Struct(Node *);
void Destroy_Struct(Node *);

// Used to generate the k sequence
int * Generate_Sequence(int);
int Number_Of_Elements(int);
int Highest_Power(int);
int Calculate_Number(int, int);


#endif /* PA02_H */
