#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "func.h"
#include "eval.h"
#include "trace.h"

int numFuncs = 0;

// Find a function metadata from the table
Func* find_function(char *name) {
  for (int i = 0; i < numFuncs; i++) {
  if (!strcmp(functions[i].name, name))
    return &functions[i];
  }
  return NULL;
}

// Define a function
void def_function(Func* fn) {

  if (numFuncs >= MAX_FUNCTIONS) {
    PANIC("ERROR: Number of defined functions exceeds %d.\n", MAX_FUNCTIONS);
    return;
  }

  if (find_function(fn->name)) {
    PANIC("ERROR: Function '%s' already defined.\n", fn->name);
    return;
  }

  functions[numFuncs++] = *fn;
}

// Call a function (basically, eval() for a function)
int call_function(char *name, AstNode *argv[], int argc, int* env) {

  // Builtin functions take precedence
  BuiltInFunc bfn = find_builtin_func(name);
  if (bfn) { return bfn(argv, argc, env); }

  // Find the function body
  Func* fn = find_function(name);

  // Did not find the function you were looking for! Scream! Run! Panic!
  if (!fn) {
    fprintf(stderr, "Function '%s' is undefined.", name);
    exit(1);
  }

  // Check the number of arguments
  if (argc != fn->argc) {
    fprintf(stderr, "%s expects %d arguments but got %d\n", name, fn->argc, argc);
    exit(1);
  }

  // Let's go on with our lives
  int *params = (int*) malloc(sizeof(int) * MAX_ARGUMENTS);
  for (int i = 0; i < argc; i++) {
    params[i] = eval(argv[i], env);
  }
  int value = eval(fn->body, params);
  free(params);
  return value;
}

BuiltInFunc find_builtin_func(char *name) {
  if (!strcmp(name, "inc")) { return &fiz_inc; }
  if (!strcmp(name, "dec")) { return &fiz_dec; }
  if (!strcmp(name, "ifz")) { return &fiz_ifz; }
  if (!strcmp(name, "halt")) { return &fiz_halt; }
  return NULL;
}

// BUILTIN FUNCTIONS
int fiz_inc(AstNode* argv[], int argc, int *env) {
  // Expect 1 argument
  if (argc != 1) {
    fprintf(stderr, "INC expects 1 argument but got %d.\n", argc);
    exit(1);
  }
  // Otherwise, eval and increment
  int value = eval(argv[0], env);
  return value + 1;
}
int fiz_dec(AstNode* argv[], int argc, int *env) {
  // Expect 1 argument
  if (argc != 1) {
    fprintf(stderr, "DEC expects 1 argument but got %d.\n", argc);
    exit(1);
  }
  // Otherwise, eval and decrement
  int value = eval(argv[0], env);
  if (value <= 0) {
    fprintf(stderr, "Attempt to (dec 0).\n");
    exit(1);
  }
  return value - 1;
}
int fiz_ifz(AstNode* argv[], int argc, int *env) {
  // Expect 3 argument
  if (argc != 3) {
    fprintf(stderr, "IFZ expects 3 arguments but got %d.\n", argc);
    exit(1);
  }
  // eval the first expression
  int cond = eval(argv[0], env);
  int value;
  if (!cond) {
    value = eval(argv[1], env);
  } else {
    value = eval(argv[2], env);
  }
  return value;
}
int fiz_halt(AstNode* argv[], int argc, int *env) {
  // Expect no arguments
  if (argc != 0) {
    fprintf(stderr, "HALT expects no arguments but got %d.\n", argc);
    exit(1);
  }
  // Panic!
  fprintf(stderr, "Halted.");
  exit(1);
}
