#ifndef TABLE_H
#define TABLE_H

#include "utils.h"

struct Table {
  short *data[2];
  uint32_t (*hashFuntion[2])(uint32_t key);
};

struct Table *createTable();
char insertData(struct Table *table, uint32_t key, short data);
char deleteData(struct Table *table, uint32_t key);
void freeTable(struct Table *table);
void printTable(struct Table *table);

#endif // !TABLE_H
