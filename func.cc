#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "func.h"
#include "trace.h"
#include "global.h"

// FIZ-scripted Functions
Func::Func() { }

Func::Func(char *n) {
  name = strdup(n);
}

Func::~Func(void) {
  delete name;
  for (int i = 0; i < argc; i++) { delete argv[i]; }
  delete body;
}

int
Func::call(AstNode *argv[], int argc, int *env) {

  #ifndef FUNC_ZERO_ARG
    if (argc == 0) {
      WARN("User-defined function calls without arguments are not allowed.\n");
      PANIC("#define FUNC_NO_ARGS to enable this behavior.\n");
    }
  #endif

  if (argc != this->argc) {
    PANIC("%s expects %d arguments but got %d\n", name, this->argc, argc);
  }

  int *params = new int[MAX_ARGUMENTS];
  for (int i = 0; i < argc; i++) { params[i] = argv[i] -> eval(env); }
  int result = body -> eval(params);
  delete params;
  return result;
}

// Native Functions
NativeFunc::NativeFunc(const char *name, int argc, BuiltInFunc native) {
  this->argc = argc;
  this->name = strdup(name);
  this->native = native;
  this->body = NULL;
}

NativeFunc::~NativeFunc(void) {
  delete name;
}

int
NativeFunc::call(AstNode *argv[], int argc, int *env) {
  return (*native)(argv, argc, env);
}

// BST
BST::BST(Func* fn) {
  key   = fn->name;
  value = fn;
  lnode = NULL;
  rnode = NULL;
}

int
BST::insert(BST* node) {
  int cond = strcmp(key, node->key);

  if (cond > 0) {
    if (rnode) { return rnode -> insert(node); }
    else {
      rnode = node;
      return 1;
    }
  }
  else if (cond < 0) {
    if (lnode) { return lnode -> insert(node); }
    else {
      lnode = node;
      return 1;
    }
  }
  else return 0;
}

BST*
BST::find(const char* key) {
  int cond = strcmp(this->key, key);

  if (cond > 0) {
    if (rnode) { return rnode -> find(key); }
    else return NULL;
  }
  else if (cond < 0) {
    if (lnode) { return lnode -> find(key); }
    else return NULL;
  }
  else return this;
}


// Function Registry
int
FuncRegistry::reg(Func* fn) {
  if (count >= MAX_FUNCTIONS + BUILTIN_FUNCTIONS) {
    PANIC("Number of defined functions exceeds %d.\n", MAX_FUNCTIONS);
  }

  BST* node = new BST(fn);
  if (!root) {
    root = node;
    count = 1;
    return 1;
  }
  else {
    int result = root -> insert(node);
    if (!result) delete node;
    else count++;
    return result;
  }
}

Func*
FuncRegistry::find(const char* name) {
  if (!root) return NULL;
  else {
    BST *node = root -> find(name);
    if (!node) { return NULL; }
    return node -> value;
  }
}


// BUILTIN FUNCTIONS
int fiz_inc(AstNode* argv[], int argc, int *env) {
  int value = argv[0] -> eval(env);
  return value + 1;
}
int fiz_dec(AstNode* argv[], int argc, int *env) {
  int value = argv[0] -> eval(env);
  if (value <= 0) { PANIC("Attempt to (dec 0).\n"); }
  return value - 1;
}
int fiz_ifz(AstNode* argv[], int argc, int *env) {
  int cond = argv[0] -> eval(env);
  int value;
  if (!cond) {
    value = argv[1] -> eval(env);
  } else {
    value = argv[2] -> eval(env);
  }
  return value;
}
int fiz_halt(AstNode* argv[], int argc, int *env) {
  // Panic!
  PANIC("Halted.");
}
