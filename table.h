#ifndef TABLE_H
#define TABLE_H

#include <stdlib.h>

struct Table {
  short *data;
};

struct Table *createTable(char prefix);
void freeTable(struct Table *table);

#endif // !TABLE_H
