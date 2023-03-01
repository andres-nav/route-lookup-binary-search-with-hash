#include "table.h"
#include "tree.h"

struct Table *createTable(char prefix) {
  struct Table *table = (struct Table *)malloc(sizeof(struct Table));
  if (table == NULL) {
    return NULL;
  }

  short *data = (short *)calloc(prefix, sizeof(short));
  if ((table->data = data) == NULL) {
    freeTable(table);
    return NULL;
  }

  return table;
}

void freeTable(struct Table *table) {
  if (table == NULL) {
    return;
  }

  if (table->data != NULL) {
    free(table->data);
  }

  free(table);
}
