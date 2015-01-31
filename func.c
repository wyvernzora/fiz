#include "func.h"

// Find a function metadata from the table
Func* find_function(char *name) {
  for (int i = 0; i < numFuncs; i++) {
  if (!strcmp(functions[i].name, name))
    return &functions[i];
  }
  return NULL;
}
