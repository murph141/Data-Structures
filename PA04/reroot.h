// Avoid double inclusion
#ifndef REROOT_H
#define REROOT_H 

typedef struct _node {
  double x, y, width, height;
  struct _node * left;
  struct _node * right;
} Node;

typedef struct _item {
  struct _item * next;
  Node * item;
} Stack;

// Used for file I/O
Node * Load_File(char *);

// Stack operations
int isEmpty(Stack *);
Stack * push(Stack *, Node *);
Node * pop(Stack **);

Node * Create_Node(double, double);
#endif /* REROOT_H */
