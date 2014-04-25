#ifndef RIVER_H
#define RIVER_H

typedef struct _node {
  int tr, tl, bl, br, trw, tlw, blw, brw;
  int branch;
  unsigned int distance;
} Node;

int Load_File(char *);
Node * Create_Graph(int, FILE *);

void Weights_Right(Node *, int);
void Weights_Left(Node *, int);
int Dijkstra(Node *, Node *);

#endif // RIVER_H
