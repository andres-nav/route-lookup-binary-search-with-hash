#include "main.h"
#include "tree.h"

int main(int argc, char *argv[]) {
  char keys[10] = {0, 1, 4, 11, 3, 2, 10, 3, 9, 5};
  struct Node *root = NULL;
  printTree(root, 0);
  for (int i = 0; i < 10; i++) {
    printf("\n-----------\n");
    root = insertNode(root, keys[i]);
    printTree(root, 0);
  }

  return 0;
}
