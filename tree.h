#ifndef TREE_H
#define TREE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

struct Node {
  char key;
  int *table;
  struct Node *left;
  struct Node *right;
  char height;
};

struct Node *createNode(char key);
struct Node *insertNode(struct Node *node, char key);
struct Node *deleteNode(struct Node *root, int key);
void printTree(struct Node *root);
struct Node *freeTree(struct Node *root);

#endif // !TREE_H
