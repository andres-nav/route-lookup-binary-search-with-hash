#include "table.h"
#include "utils.h"

/* #define TABLE_SIZE_DEFAULT 5000 // number of slots in each table */
#define TABLE_SIZE_DEFAULT 10 // number of slots in each table
#define MAX_ATTEMPTS 50       // maximum number of attempts to insert a key

// TODO try to optimize this functions with pointers
static uint32_t hash1(uint32_t key, unsigned int table_size) {
  uint32_t hash = key;
  hash ^= hash >> 16;
  hash *= 0x85ebca6b;
  hash ^= hash >> 13;
  hash *= 0xc2b2ae35;
  hash ^= hash >> 16;
  return hash % table_size;
}

static uint32_t hash2(uint32_t key, unsigned int table_size) {
  uint32_t hash = key;
  hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
  hash = ((hash >> 16) ^ hash) * 0x01d8fff;
  hash = ((hash >> 16) ^ hash) * 0xaad003b;
  hash = (hash >> 16) ^ hash;
  return hash % table_size;
}

struct Table *createTable(char prefix) {
  struct Table *table = (struct Table *)malloc(sizeof(struct Table));
  if (table == NULL) {
    raise(ERROR_MEMORY_ALLOCATION);
    return NULL;
  }

  for (unsigned char i = 0; i < NUMBER_TABLES; i++) {
    table->entries[i] = NULL;
  }

  table->size = TABLE_SIZE_DEFAULT;

  for (unsigned char i = 0; i < NUMBER_TABLES; i++) {
    table->entries[i] =
        (struct Entry *)calloc(table->size, sizeof(struct Entry));
    if (table->entries[i] == NULL) {
      freeTable(table);
      raise(ERROR_MEMORY_ALLOCATION);
      return NULL;
    }

    table->entries[i]->key = -1;
    table->entries[i]->label = LABEL_DEFAULT;
    table->entries[i]->data = -1;
  }

  table->prefix = prefix;
  table->hashFuntion[0] = hash1;
  table->hashFuntion[1] = hash2;

  return table;
}

char insertData(struct Table *table, uint32_t key, enum EntryLabel label,
                short data) {
  if (table == NULL) {
    return raise(ERROR_EMPTY_POINTER);
  }

  for (unsigned char i = 0; i < MAX_ATTEMPTS; i++) {
    unsigned char index = i % NUMBER_TABLES;
    uint32_t hash = table->hashFuntion[index](key, table->size);

    if (table->entries[index][hash].key == key) {
      return ERROR_TABLE_DOUBLE_INSERT;
    }

    if (table->entries[index][hash].label == LABEL_DEFAULT) {
      table->entries[index][hash].key = key;
      table->entries[index][hash].label = label;
      table->entries[index][hash].data = data;

      return OK;
    } else {
      uint32_t tmp_key = table->entries[index][hash].key;
      enum EntryLabel tmp_label = table->entries[index][hash].label;
      short tmp_data = table->entries[index][hash].data;

      table->entries[index][hash].key = key;
      table->entries[index][hash].label = label;
      table->entries[index][hash].data = data;

      key = tmp_key;
      label = tmp_label;
      data = tmp_data;
    }
  }

  return raise(ERROR_TABLE_MAX_ATTEMPTS);
}

char deleteData(struct Table *table, uint32_t key) {
  if (table == NULL) {
    return raise(ERROR_EMPTY_POINTER);
  }

  struct Entry *entry = findEntry(table, key);
  if (entry == NULL) {
    return raise(ERROR_TABLE_NO_ENTRY);
  }

  entry->key = 0;
  entry->label = LABEL_DEFAULT;
  entry->data = 0;

  return OK;
}

struct Entry *findEntry(struct Table *table, uint32_t key) {
  if (table == NULL) {
    raise(ERROR_EMPTY_POINTER);
    return NULL;
  }

  for (unsigned char i = 0; i < NUMBER_TABLES; i++) {
    uint32_t hash = table->hashFuntion[i](key, table->size);
    if (table->entries[i][hash].key == key) {
      return &(table->entries[i][hash]);
    }
  }

  return NULL;
}

void freeTable(struct Table *table) {
  if (table == NULL) {
    return;
  }

  for (unsigned char i = 0; i < NUMBER_TABLES; i++) {
    if (table->entries[i] != NULL) {
      free(table->entries[i]);
    }
  }

  free(table);
}

void printTable(struct Table *table) {
  if (table == NULL) {
    return;
  }

  for (unsigned char i = 0; i < NUMBER_TABLES; i++) {
    printf("\tPrinting table %u\n", i);

    if (table->entries[i] == NULL) {
      continue;
    }

    struct Entry *entry_array = table->entries[i];

    for (unsigned int j = 0; j < table->size; j++) {
      if (entry_array[j].label != LABEL_DEFAULT) {
        char label = entry_array[j].label == LABEL_PREFIX ? 'P' : 'M';

        char *ip = malloc(16 * sizeof(char));
        getIPString(&ip, entry_array[j].key);

        printf("\t\tL:%c K:%s D:%d\n", label, ip, entry_array[j].data);

        free(ip);
      }
    }
  }
}
