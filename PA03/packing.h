#ifndef PACKING_H
#define PACKING_H

typedef struct node {
  int left;
  int right;
  int parent;
  double height;
  double width;
  char slice;
} Node;

Node * Load_File(char *);
Node * Fix_Values(Node *);

void Special_Post_Order(Node *, int);

// Used for the screen dump
void Screen_Dump(Node *);
void Post_Order(Node *, int);
void Pre_Order(Node *, int);
void In_Order(Node *, int);

#endif /* PACKING_H */
