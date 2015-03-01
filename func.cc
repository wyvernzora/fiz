// ------------------------------------------------------------------------- //
//                                                                           //
// CS252 Lab02 - FIZ Interpreter                                             //
// Copyright © 2015 Denis Luchkin-Zhou                                       //
//                                                                           //
// func.cc                                                                   //
// This file contains the logic for FIZ function structures, FIZ function    //
// registry and builtin functions.                                           //
//                                                                           //
// ------------------------------------------------------------------------- //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fiz.h"
#include "ast.h"
#include "func.h"

// Forward declaration
FuncMap FuncRegistry::map;


// ========================================================================= //
// Base Class for all functions.                                             //
// ========================================================================= //

// Call: no-op.
int Func::call(NodeList *args, int *context) { }


// ========================================================================= //
// Function scripted in FIZ.                                                 //
// ========================================================================= //

// Constructor. Takes a name, list of arguments and an AST node body.
UserFunc::UserFunc(char *name, IdList *args, AstNode *body) {
  this -> name = name;
  this -> args = args ? args : new IdList();
  this -> argc = args ? args -> size() : 0;
  this -> body = body;
}

// Destructor.
UserFunc::~UserFunc() {
  free(name);
  while (!args -> empty()) {
    char *arg = args -> front();
    args -> pop_front();
    free(arg);
  }
  if (body) { delete body; }
}

// Call: creates a context from arguments and evaluates the function body AST.
// Takes a list of AST nodes as arguments, and the parent context.
int UserFunc::call(NodeList *args, int *context) {
  // Check the number of arguments
  int argc  = args -> size();
  if (argc != this -> argc) { throw FIZ_ARGNUM; }
  // Evaluate all arguments
  int *params = new int[argc];
  for (int i = 0; i < argc; i++) {
    params[i] = args -> at(i) -> eval(context);
  }
  // Evaluate the function body AST
  int result = body -> eval(params);
  delete params;
  return result;
}


// ========================================================================= //
// Native function that is exposed to the FIZ runtime.                       //
// ========================================================================= //

// Constructor. Takes a function name, number of arguments and a pointer to
// the function to expose.
NativeFunc::NativeFunc(const char *name, int argc, BuiltInFunc native) {
  this->argc = argc;
  this->name = strdup(name);
  this->native = native;
}

// Call: passes arguments to the native handler.
int NativeFunc::call(NodeList *args, int *env) {
  return (*native)(args, env);
}


// ========================================================================= //
// Function registry that maps function names to executable code.            //
// ========================================================================= //

// Init: adds builtin functions to the map.
void FuncRegistry::init() {
  reg(new NativeFunc("inc",  1, fiz_inc));
  reg(new NativeFunc("dec",  1, fiz_dec));
  reg(new NativeFunc("ifz",  3, fiz_ifz));
  reg(new NativeFunc("halt", 0, fiz_hlt));
}

// Registers the function: returns true if successful; false otherwise.
bool FuncRegistry::reg(Func* fn) {
  if (map[fn -> name]) { return false; }
  map[fn -> name] = fn;
  return true;
}

// Retrieves a function with a given name. Returns NULL if not found.
Func* FuncRegistry::find(char* name) {
  return map[name];
}


// ========================================================================= //
// Builtin function handlers.                                                //
// ========================================================================= //

int fiz_inc(NodeList *args, int *env) {
  int value = args -> at(0) -> eval(env);
  return value + 1;
}
int fiz_dec(NodeList *args, int *env) {
  int value = args -> at(0) -> eval(env);
  if (value <= 0) { throw FIZ_DEC_ZERO; }
  return value - 1;
}
int fiz_ifz(NodeList *args, int *env) {
  int cond = args -> at(0) -> eval(env);
  printf("cond = %d\n", cond);
  int value;
  if (!cond) {
    value = args -> at(1) -> eval(env);
  } else {
    value = args -> at(2) -> eval(env);
  }
  printf("value = %d\n", value);
  return value;
}
int fiz_hlt(NodeList *args, int *env) {
  throw FIZ_HALT;
}
