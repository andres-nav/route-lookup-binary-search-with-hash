#include "table.h"

#define TABLE_SIZE 1000 // number of slots in each table
#define MAX_ATTEMPTS 10 // maximum number of attempts to insert a key

// TODO try to optimize this functions with pointers
static uint32_t hash1(uint32_t key) {
  uint32_t hash = key;
  hash ^= hash >> 16;
  hash *= 0x85ebca6b;
  hash ^= hash >> 13;
  hash *= 0xc2b2ae35;
  hash ^= hash >> 16;
  return hash % TABLE_SIZE;
}

static uint32_t hash2(uint32_t key) {
  uint32_t hash = key;
  hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
  hash = ((hash >> 16) ^ hash) * 0x01d8fff;
  hash = ((hash >> 16) ^ hash) * 0xaad003b;
  hash = (hash >> 16) ^ hash;
  return hash % TABLE_SIZE;
}

/* static uint32_t hash3(uint32_t key) { */
/*   uint32_t hash = key; */
/*   hash += ~(hash << 15); */
/*   hash ^= (hash >> 10); */
/*   hash += (hash << 3); */
/*   hash ^= (hash >> 6); */
/*   hash += ~(hash << 11); */
/*   hash ^= (hash >> 16); */
/*   return hash % TABLE_SIZE; */
/* } */

static char findData(short *array, short data) {
  if (array == NULL) {
    return -1;
  }

  for (unsigned int i = 0; i < TABLE_SIZE; i++) {
    if (array[i] == data) {
      return i;
    }
  }

  return -2;
}

struct Table *createTable() {
  struct Table *table = (struct Table *)malloc(sizeof(struct Table));
  if (table == NULL) {
    return NULL;
  }

  short *data1 = (short *)calloc(TABLE_SIZE, sizeof(short));
  short *data2 = (short *)calloc(TABLE_SIZE, sizeof(short));
  if (((table->data[0] = data1) == NULL) ||
      ((table->data[1] = data2) == NULL)) {
    freeTable(table);
    return NULL;
  }

  table->hashFuntion[0] = hash1;
  table->hashFuntion[1] = hash2;

  return table;
}

char insertData(struct Table *table, uint32_t key, short data) {
  if (table == NULL) {
    return -1;
  }

  for (unsigned char i = 0; i < MAX_ATTEMPTS; i++) {
    unsigned char index = i % 2;
    uint32_t hash = table->hashFuntion[index](key);

    if (table->data[index][hash] == 0) {
      table->data[index][hash] = data;
      return 0;
    } else {
      short tmp = table->data[index][hash];

      table->data[index][hash] = data;
      data = tmp;
    }
  }

  printf("Error max attempts %d\n", key);

  return -2;
}

char deleteData(struct Table *table, uint32_t key) {
  if (table == NULL) {
    return -1;
  }

  for (unsigned char i = 0; i < 2; i++) {
    int index = findData(table->data[i], key);
    if (index >= 0) {
      table->data[i][index] = 0;
    }
  }

  printf("Entry not found.\n");
  return -2;
}

void freeTable(struct Table *table) {
  if (table == NULL) {
    return;
  }

  if (table->data[0] != NULL) {
    free(table->data[0]);
  }

  if (table->data[1] != NULL) {
    free(table->data[1]);
  }

  free(table);
}

static void printData(short *data) {
  for (unsigned int i = 0; i < TABLE_SIZE; i++) {
    if (data[i] != 0) {
      printf("%d\n", data[i]);
    }
  }
}

void printTable(struct Table *table) {
  if (table == NULL) {
    return;
  }

  for (unsigned char i = 0; i < 2; i++) {
    printf("Printing table %u\n", i);
    printData(table->data[i]);
  }
}
