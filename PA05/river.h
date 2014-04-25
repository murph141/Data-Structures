#ifndef RIVER_H
#define RIVER_H

typedef struct _node {
  int tr, tl, bl, br, trw, tlw, blw, brw;
  int branch;
} Node;

Node * Load_File(char *);
Node * Create_Graph(int, FILE *);

#endif // RIVER_H
