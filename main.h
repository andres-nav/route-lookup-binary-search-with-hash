#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

#include "io.h"
#include "table.h"
#include "tree.h"

struct LMPInfo {
  struct Node *root;
  uint32_t ip;
  unsigned short *outInterface;
  unsigned char *tableAccesses;
};

int main(int argc, char *argv[]);

#endif // !MAIN_H
