#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "func.h"
#include "eval.h"
#include "trace.h"
#include "global.h"

Func::Func() { }

Func::Func(char *n) {
  name = strdup(n);
}

Func::~Func(void) {
  delete name;
  for (int i = 0; i < argc; i++) { delete argv[i]; }
  delete body;
}

int Func::call(AstNode *argv[], int argc, int *env) {
  if (argc != this->argc) {
    PANIC("%s expects %d arguments but got %d\n", name, this->argc, argc);
  }

  int *params = new int[MAX_ARGUMENTS];
  for (int i = 0; i < argc; i++) { params[i] = eval(argv[i], env); }
  int result = eval(body, params);
  delete params;
  return result;
}


NativeFunc::NativeFunc(const char *name, int argc, BuiltInFunc native) {
  this->argc = argc;
  this->name = strdup(name);
  this->native = native;
}

NativeFunc::~NativeFunc(void) {
  delete name;
}

int NativeFunc::call(AstNode *argv[], int argc, int *env) {
  return (*native)(argv, argc, env);
}


// Find a function metadata from the table
Func * find_function(char *name) {
  for (int i = 0; i < numFuncs; i++) {
  if (!strcmp(functions[i] -> name, name))
    return functions[i];
  }
  return NULL;
}

// Define a function
void registerFunction(Func* fn) {

  if (numFuncs >= MAX_FUNCTIONS + BUILTIN_FUNCTIONS) {
    PANIC("ERROR: Number of defined functions exceeds %d.\n", MAX_FUNCTIONS);
  }

  if (find_function(fn->name)) {
    PANIC("ERROR: Function '%s' already defined.\n", fn->name);
  }

  functions[numFuncs++] = fn;
}

// Call a function (basically, eval() for a function)
int call_function(char *name, AstNode *argv[], int argc, int* env) {

  // Find the function body
  Func* fn = find_function(name);

  // Did not find the function you were looking for! Scream! Run! Panic!
  if (!fn) { PANIC("Function '%s' is undefined.", name); }


  // Check the number of arguments
  if (argc != fn->argc) {
    PANIC("ERROR: %s expects %d argument%s but got %d.\n", name,
      fn->argc, (fn->argc == 1 ? "" : "s"), argc);
  }

  // Let's go on with our lives
  return fn->call(argv, argc, env);
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
  int value = eval(argv[0], env);
  return value + 1;
}
int fiz_dec(AstNode* argv[], int argc, int *env) {
  int value = eval(argv[0], env);
  if (value <= 0) { PANIC("Attempt to (dec 0).\n"); }
  return value - 1;
}
int fiz_ifz(AstNode* argv[], int argc, int *env) {
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
  // Panic!
  PANIC("Halted.");
  exit(1);
}
