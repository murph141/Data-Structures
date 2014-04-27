#ifndef RIVER_H
#define RIVER_H

typedef struct _node {
  int x, y; // X and Y Coordinates
  int * adj;
  int * dist; // Distance to a specified node
} Node;

typedef struct _heap {
  int number;
  int dist;
  //int weight;
} Heap;

int Load_File(char *);
Node * Create_Graph(FILE *);
void Create_Adjacency(Node *, int);

void Calculate_Distance(Node *, int);
int IsInCone(int, int, int, int);

int Dijkstra(Node *);
int Extract_Min(Heap *, int);
void Downward_Heapify(Heap *, int, int);
void Check_Adjacent(Heap *, Node *, int, int);
void swap(Heap *, int, int);
int FindPQ(Heap *, int, int);
void FreeData(Node *);

#endif // RIVER_H
