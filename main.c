#include "main.h"
#include "io.h"
#include "tree.h"

static struct Node *generateTree() {
  uint32_t prefix;
  int prefixLength, outInterface;

  resetIO();
  struct Node *root = NULL;

  while (readFIBLine(&prefix, &prefixLength, &outInterface) != REACHED_EOF) {
    root = insertNode(root, prefixLength);
  }
  printTree(root);

  resetIO();
  return root;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    return -1;
  }
  char *fib = argv[1];
  char *input = argv[2];

  initializeIO(fib, input);

  struct Node *root = NULL;
  root = generateTree();

  freeIO();
  return 0;
}
