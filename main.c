#include "main.h"

int main(int argc, char *argv[]) {
  char keys[15] = {0, 6, 7, 8, 9, 16, 17, 19, 26, 28, 32};
  struct Node *root = NULL;
  for (int i = 0; i < 15; i++) {
    root = insertNode(root, keys[i]);
  }

  printTree(root);

  freeTree(root);
  return 0;
}
