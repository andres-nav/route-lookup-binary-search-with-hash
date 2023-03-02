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

    insertData(table, prefix, outInterface, LABEL_PREFIX);
  }
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
  printTree(root);

  fillTreeWithPrefixes(root);

  for (int i = 0; i < 33; i++) {
    printf("prefix %d\n", i);
    printTable(getTableFromNode(root, i));
  }

  freeTree(root);

  freeIO();
  return 0;
}

/* int main(int argc, char **argv) { */
/*   fillTreeWithPrefixes(NULL); */
/*   struct Table *table = createTable(); */
/*   if (table == NULL) { */
/*     printf("error\n"); */
/*     return -1; */
/*   } */
/**/
/*   uint32_t ip[10] = {0xFFA1, 0x0301, 0x0303, 0x2300, 0xAAAA, */
/*                      0x0231, 0x0494, 0x2039, 0x0239, 0x1234}; */
/**/
/*   for (char i = 0; i < 10; i++) { */
/*     insertData(table, ip[i], i + 1, LABEL_PREFIX); */
/*   } */
/*   printTable(table); */
/**/
/*   freeTable(table); */
/**/
/*   return 0; */
/* } */
