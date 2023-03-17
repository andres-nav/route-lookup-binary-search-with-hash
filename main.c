#include "main.h"
#include "table.h"
#include "tree.h"

static struct Node *generateTree() {
  uint32_t prefix;
  int prefixLength, outInterface;

  resetIO();
  struct Node *root = NULL;

  while (readFIBLine(&prefix, &prefixLength, &outInterface) != REACHED_EOF) {
    root = insertNode(root, prefixLength);
  }

  return root;
}

static void fillTreeWithPrefixes(struct Node *root) {
  uint32_t prefix;
  int prefixLength, outInterface;

  resetIO();

  int previousPrefixLength = -1;
  struct Table *table;

  while (readFIBLine(&prefix, &prefixLength, &outInterface) != REACHED_EOF) {
    if (prefixLength != previousPrefixLength) {
      table = getTableFromNode(root, prefixLength);
    }

    insertData(table, prefix, LABEL_PREFIX, outInterface);
  }
}

static void addMarkers(struct Node *root) {}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    return -1;
  }
  char *fib = argv[1];
  char *input = argv[2];

  initializeIO(fib, input);

  struct Node *root = NULL;
  root = generateTree();

  fillTreeWithPrefixes(root);

  printTree(root);

  freeTree(root);

  freeIO();
  return 0;
}
