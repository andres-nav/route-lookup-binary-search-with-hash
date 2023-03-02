#include "utils.h"

/********************************************************************
 * Generate a netmask of length prefixLength
 ********************************************************************/
void getNetmask(int prefixLength, int *netmask) {

  *netmask = (0xFFFFFFFF << (IP_ADDRESS_LENGTH - prefixLength));
}

/********************************************************************
 * Example of a very simple hash function using the modulus operator
 * For more info: https://gist.github.com/cpq/8598442
 ********************************************************************/
int hash(uint32_t IPAddress, int sizeHashTable) {

  // Map the key (IPAddress) to the appropriate index of the hash table
  int index = IPAddress % sizeHashTable;
  return (index);
}

/*
 * Return the max of two integers
 */
char max(char a, char b) { return (a > b) ? a : b; }

float getSizePrefix(char prefix) { return (powf(2, prefix)); }

static void printError(const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  printf("!!!!!!!!!!!!!!! ERROR: ");
  printf(format, ap);
  printf(" !!!!!!!!!!!!!!!\n");
  va_end(ap);
}

enum Error raise(enum Error error) {
  switch (error) {
  case ERROR_EMPTY_POINTER:
    printError("Empty pointer detected");
    break;
  case ERROR_MEMORY_ALLOCATION:
    printError("Memory allocation error");
    break;

  case ERROR_TABLE_DOUBLE_INSERT:
    printError("Trying to insert a key in a table that is already there");
    break;
  case ERROR_TABLE_MAX_ATTEMPTS:
    printError("Max attempts reached inserting a key");
    break;
  case ERROR_TABLE_NO_ENTRY:
    printError("No entry in the given table");
    break;
  }

  return error;
}
