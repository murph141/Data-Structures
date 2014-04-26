#ifndef RIVER_H
#define RIVER_H

typedef struct _node {
  int tr, trw;
  int tl, tlw;
  int br, brw;
  int bl, blw;
  int up, upw;
  int dn, dnw;
  int branch;
} Node;

typedef struct _heap {
  int nn;
  int dist;
} Heap;

int Load_File(char *);
Node * Create_Graph(int, FILE *);

void Weights_Left(Node *, int);
void Weights_Right(Node *, int);
int Dijkstra(int, Node *, int);

void Check_Dist(Node *, Heap *, int);
void Downward_Heapify(Heap *, int, int);
int Extract_Min(Heap *, int);
int IsInPQ(int, Heap *, int);

#endif // RIVER_H
