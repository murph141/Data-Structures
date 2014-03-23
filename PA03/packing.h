// Avoid double inclusion
#ifndef PACKING_H
#define PACKING_H

// Node structure
// Since I implemented an array, the left and right values are stored as integers instead of pointers
//    Each left and right node of a given node can be accessed by using arr[arr[index].left]
// I allocated space for n+1 nodes (So I could access values 1 to n)
//    Because of this arr[0] is not used in the tree structure
//    However, it is used as storage for the total number of nodes to avoid the use of a pointer
//
// The height and width are stored as doubles
// The x and y coordinates are stored as doubles
// The slicing of the node is stored as a characters
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
Node * Load_File(char *);
int Save_File(Node *, char *); // Returns a 0 or 1 (0 if successful, 1 if unsuccessful)

// Fill in height and width values of non-leaf nodes, since leaf nodes' values were stored during the file loading
void Special_Post_Order(Node *, int);

// Fill in corrdinates
void Coordinates(Node *, int);

// Used for the screen dump
void Screen_Dump(Node *);

// Assorted tree traversals
void Post_Order(Node *, int);
void Pre_Order(Node *, int);
void In_Order(Node *, int);

#endif /* PACKING_H */
