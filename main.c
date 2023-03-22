#include "main.h"
#include "table.h"
#include "tree.h"
#include "utils.h"
#include <stdint.h>

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
  if (root == NULL) {
    raise(ERROR_NODE_NOT_FOUND);
    return;
  }

  uint32_t ip, prefix;
  int prefixLength, outInterface;

  resetIO();

  int previousPrefixLength = -1;
  struct Table *table = NULL;

  while (readFIBLine(&ip, &prefixLength, &outInterface) != REACHED_EOF) {
    if (prefixLength != previousPrefixLength) {
      table = getTableFromNode(root, prefixLength);
    }

    getPrefix(ip, prefixLength, &prefix);
    insertData(table, prefix, LABEL_PREFIX, outInterface);
  }
}

static void addMarkersFromTableToNode(struct Node *node, struct Table *table) {
  for (unsigned char i = 0; i < NUMBER_TABLES; i++) {
    if (table->entries[i] == NULL) {
      continue;
    }

    struct Entry *entry_array = table->entries[i];
    uint32_t key = 0;

    for (unsigned int j = 0; j < table->size; j++) {
      if (entry_array[j].label != LABEL_DEFAULT) {
        getPrefix(entry_array[j].key, node->key, &key);

        insertData(node->table, key, LABEL_MARK, -1);
      }
    }
  }
}

static void computeMarkersForSubtree(struct Node *node) {
  if (node == NULL) {
    return;
  }

  if (node->right == NULL) {
    return;
  }

  computeMarkersForSubtree(node->right);
  addMarkersFromTableToNode(node, node->right->table);

  struct Node *left_node = node->right->left;
  while (left_node != NULL) {
    computeMarkersForSubtree(left_node);
    addMarkersFromTableToNode(node, left_node->table);
    left_node = left_node->left;
  }
}

static void fillTreeWithMarkers(struct Node *root) {
  if (root == NULL) {
    raise(ERROR_NODE_NOT_FOUND);
    return;
  }

  do {
    computeMarkersForSubtree(root);
  } while ((root = root->left) != NULL);
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

  fillTreeWithPrefixes(root);
  fillTreeWithMarkers(root);

  printTree(root);

  freeTree(root);

  freeIO();
  return 0;
}
