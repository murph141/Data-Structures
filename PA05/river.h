#ifndef RIVER_H
#define RIVER_H

typedef struct _node {
  struct _node * tl;
  struct _node * tr;
  struct _node * bl;
  struct _node * br;
  int plank;
} Node;

Node * Load_File(char *);
Node * Create_Graph(int, FILE *);

#endif // RIVER_H
