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

//Create the structure of values
Node * Create_Node(long);
void Print_Struct(Node *);
void Destroy_Struct(Node *);

#endif /* PA02_H */
