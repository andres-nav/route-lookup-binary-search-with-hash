#ifndef TABLE_H
#define TABLE_H

#include "utils.h"

#define NUMBER_TABLES 2 // number of tables used in cucko hashing

enum EntryLabel {
  LABEL_DEFAULT = 0,
  LABEL_PREFIX = 1,
  LABEL_MARK = 2,
  LABEL_PREFIX_MARK = 3,
};

struct Entry {
  uint32_t key;
  enum EntryLabel label;
  short data;
  struct Table *bmp;
};

struct Table {
  struct Entry *entries[NUMBER_TABLES];
  uint32_t (*hashFuntion[NUMBER_TABLES])(uint32_t key);
};

struct Table *createTable();
char insertData(struct Table *table, uint32_t key, enum EntryLabel label,
                short data);
char deleteData(struct Table *table, uint32_t key);
struct Entry *findEntry(struct Table *table, uint32_t key);
void freeTable(struct Table *table);
void printTable(struct Table *table);

#endif // !TABLE_H
