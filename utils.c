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
  printf("\n!!!!!!!!!!!!!!! ERROR: ");
  printf(format, ap);
  printf(" !!!!!!!!!!!!!!!\n\n");
  va_end(ap);
}

enum Error raise(enum Error error) {
  switch (error) {
  case OK:
    break;
  case REACHED_EOF:
    break;
  case ERROR_EMPTY_POINTER:
    printError("Empty pointer detected");
    break;
  case ERROR_MEMORY_ALLOCATION:
    printError("Memory allocation error");
    break;
  case ERROR_WRONG_PARAMETERS:
    printError("The parameters of the functions are not correct");
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

  case ERROR_NODE_NOT_FOUND:
    printError("Not node found with given key");
    break;

  case ERROR_IO_ROUTING_TABLE_NOT_FOUND:
    printError("The routing table file could not be found");
    break;
  case ERROR_IO_INPUT_FILE_NOT_FOUND:
    printError("The input file could not be found");
    break;
  case ERROR_IO_BAD_ROUTING_TABLE:
    printError("The routing table has a bad format");
    break;
  case ERROR_IO_BAD_INPUT_FILE:
    printError("The input file has a bad format");
    break;
  case ERROR_IO_PARSE_ERROR:
    printError("There was an error parsing the files");
    break;
  case ERROR_IO_CANNOT_CREATE_OUTPUT:
    printError("Could not create the output file");
    break;
  }

  return error;
}
