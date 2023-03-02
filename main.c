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

/* int main(int argc, char *argv[]) { */
/*   if (argc != 3) { */
/*     return -1; */
/*   } */
/*   char *fib = argv[1]; */
/*   char *input = argv[2]; */
/**/
/*   initializeIO(fib, input); */
/**/
/*   struct Node *root = NULL; */
/*   root = generateTree(); */
/*   printTree(root); */
/**/
/*   fillTreeWithPrefixes(root); */
/**/
/*   for (int i = 0; i < 33; i++) { */
/*     printf("prefix %d\n", i); */
/*     printTable(getTableFromNode(root, i)); */
/*   } */
/**/
/*   freeTree(root); */
/**/
/*   freeIO(); */
/*   return 0; */
/* } */

int main(int argc, char **argv) {
  struct Table *table = createTable(16);
  if (table == NULL) {
    printf("error\n");
    return -1;
  }

  uint32_t ip[11] = {0xFFA1, 0x0301, 0x0303, 0x2300, 0xAAAA, 0x0231,
                     0x0494, 0x2039, 0x0230, 0x1234, 0xAAAA};

  for (char i = 0; i < 11; i++) {
    insertData(table, ip[i], LABEL_PREFIX, i);
    printTable(table);
  }

  freeTable(table);

  return 0;
}
