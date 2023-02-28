#ifndef TREE_H
#define TREE_H

#include <stdint.h>

struct Node {
  char key;
  int *table;
  struct Node *left;
  struct Node *right;
  char height;
};

#endif // !TREE_H
