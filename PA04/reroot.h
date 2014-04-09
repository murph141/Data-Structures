// Avoid double inclusion
#ifndef REROOT_H
#define REROOT_H 

typedef struct _node {
  double x, y, width, height;
  struct _node * left;
  struct _node * right;
  char slice;
} Node;

typedef struct _item {
  struct _item * next;
  Node * item;
} Stack;

// Used for file I/O
Node * Load_File(char *);
int Save_File(Node *, char *);
void Save_File_Helper(FILE *, Node *, int *);

// Stack operations
int isEmpty(Stack *);
void push(Stack **, Node *);
Node * pop(Stack **);

// Used to fix the coordinates (PA03 stuff)
void Special_Post_Order(Node *);
void Coordinates(Node *);

// Screen dump
void Screen_Dump(Node *);
void Pre_Order(Node *);
void In_Order(Node *);
void Post_Order(Node *);

// Creation and deletion
Node * Create_Node(double, double, char);
void destroy_Tree(Node *);

void Reroot(double *, double *, Node *, double, double, double, double, char);
#endif /* REROOT_H */
