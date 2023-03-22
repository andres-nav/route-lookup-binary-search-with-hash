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

  uint32_t ip;
  int prefixLength, outInterface;

  resetIO();

  int previousPrefixLength = -1;
  struct Table *table = NULL;

  while (readFIBLine(&ip, &prefixLength, &outInterface) != REACHED_EOF) {
    if ((outInterface < 0) || (outInterface >= 0xff)) {
      raise(ERROR_IO_OUTPUT_INTERFACE);
      continue;
    }
    if (prefixLength != previousPrefixLength) {
      table = getTableFromNode(root, prefixLength);
    }

    insertData(table, ip, LABEL_PREFIX, outInterface);
  }
}

static void addMarkersFromTableToNode(struct Node *node, struct Table *table) {
  if ((node == NULL) || (table == NULL)) {
    raise(ERROR_EMPTY_POINTER);
    return;
  }

  for (unsigned char i = 0; i < NUMBER_TABLES; i++) {
    if (table->entries[i] == NULL) {
      continue;
    }

    struct Entry *entry_array = table->entries[i];

    for (unsigned int j = 0; j < table->size; j++) {
      if (entry_array[j].label != LABEL_DEFAULT) {
        insertData(node->table, entry_array[j].key, LABEL_MARKER, -1);
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
    raise(ERROR_EMPTY_POINTER);
    return;
  }

  do {
    computeMarkersForSubtree(root);
  } while ((root = root->left) != NULL);
}

static unsigned short findLongestMatchingPrefix(struct Node *root,
                                                uint32_t ip) {
  if (root == NULL) {
    raise(ERROR_EMPTY_POINTER);
    return -1;
  }

  unsigned short lmp = -1;
  struct Entry *entry = NULL;
  do {
    entry = findEntry(root->table, ip);
    if (entry == NULL) {
      root = root->left;
    } else {
      lmp = entry->data;
      root = root->right;
    }
  } while (root != NULL);
  printf("lmp: %u ip: %u", lmp, ip);

  return lmp;
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
