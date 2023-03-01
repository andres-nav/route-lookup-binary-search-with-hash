#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/********************************************************************
 * Constant definitions
 ********************************************************************/
#define IP_ADDRESS_LENGTH 32

/********************************************************************
 * Generate a netmask of length prefixLength
 ********************************************************************/
void getNetmask(int prefixLength, int *netmask);

/********************************************************************
 * Example of a very simple hash function using the modulus operator
 * For more info: https://gist.github.com/cpq/8598442
 ********************************************************************/
int hash(uint32_t IPAddress, int sizeHashTable);

char max(char a, char b);
float getSizePrefix(char prefix);

#endif // !UTILS_H
