#include "ast.h"
#include "func.h"
#include "eval.h"

// Find a function metadata from the table
Func* find_function(char *name) {
  for (int i = 0; i < numFuncs; i++) {
  if (!strcmp(functions[i].name, name))
    return &functions[i];
  }
  return NULL;
}

// Define a function
void def_function(char *name, char *argv[], int argc, AstNode *body) {
  printf("function definition: %s\n", name);
  printf("Function defs not yet implemented.\n");
  exit(1);
  //Func* fn = (Func*) malloc(sizeof(Func));
  //fn->name = name;
}

// Call a function (basically, eval() for a function)
int call_function(char *name, char *argv[], int argc) {
  printf("function call: %s\n", name);
  printf("Function calls not yet implemented.\n");
  exit(1);
  return 0;
}
