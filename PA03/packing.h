// Avoid double inclusion
#ifndef PACKING_H
#define PACKING_H

// Node structure
typedef struct node {
  int left;
  int right;
  double height;
  double width;
  double x;
  double y;
  char slice;
} Node;

// File I/O
int Save_File(Node *, char *);
Node * Load_File(char *);

// Fill in height and width values
void Special_Post_Order(Node *, int);

// Fill in corrdinates
void Coordinates(Node *, int);

// Used for the screen dump
void Screen_Dump(Node *);
void Post_Order(Node *, int);
void Pre_Order(Node *, int);
void In_Order(Node *, int);

#endif /* PACKING_H */
