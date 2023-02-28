#ifndef TREE_H
#define TREE_H

#include <stdint.h>

struct Node {
  struct Node *left;
  struct Node *right;
  int table[];
};

#endif // !TREE_H
