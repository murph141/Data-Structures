#ifndef RIVER_H
#define RIVER_H

typedef struct _node {
  int x, y; // X and Y Coordinates
  int * adj;
  int * dist; // Distance to a specified node
} Node;

/*
typedef struct _heap {
  int nn;
  int dist;
} Heap;
*/

int Load_File(char *);
Node * Create_Graph(FILE *);
void Create_Adjacency(Node *, int);

void Calculate_Distance(Node *, int);
int IsInCone(int, int, int, int);

#endif // RIVER_H
