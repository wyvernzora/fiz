// ------------------------------------------------------------------------- //
//                                                                           //
// CS252 Lab02 - FIZ Interpreter                                             //
// Copyright © 2015 Denis Luchkin-Zhou                                       //
//                                                                           //
// ast.c                                                                     //
// This file contains the logic of abstract syntax tree nodes.               //
//                                                                           //
// ------------------------------------------------------------------------- //
#include <stdlib.h>
#include "func/func.h"
#include "ast/ast.h"


// ========================================================================= //
// Abstract base class for all AST nodes.                                    //
// ========================================================================= //

// Resolve: no-op.
void AstNode::resolve(Func *fn)   { }

// Evaluate: no-op.
int  AstNode::eval(int *env)      { return 0; }


// ========================================================================= //
// Number: represents a positive integer value as entered into the FIZ.      //
// ========================================================================= //

// Constructor: takes the value of the number.
NumNode::NumNode(int value)  { this -> value = value; }

// Resolve: no-op.
void NumNode::resolve(Func *fn)   { }

// Evaluate: returns the value.
int  NumNode::eval(int* env)      { return value; }


// ========================================================================= //
// Variable: an identifier that refers to an integer value.                  //
// ========================================================================= //

// Constructor: takes the name of the variable.
VariableNode::VariableNode(char* name) {
  this -> name = name;
  index = -1;
}

// Destructor
VariableNode::~VariableNode()     { free(name); }

// Resolve: finds the index of the variable in the function argument list.
void VariableNode::resolve(Func *fn) {
  UserFunc *ufn = (UserFunc*)fn;

  // if function definition is NULL, this variable shouldn't be here
  if (!fn) { throw FIZ_SYNTAX_ERROR; }

  // Look for the matching variable name
  int i    = 0,
      argc = ufn -> args -> size();
  for (; i < argc; i++) {
    if (!strcmp(ufn -> args -> at(i), name)) {
      index = i;
      break;
    }
  }

  // If still not found, the variable is undefined. panic.
  if (index < 0) { throw FIZ_UNDEF_VAR; }
}

// Evaluate: return the corresponding value from function argument list.
int  VariableNode::eval(int *env) { return env[index]; }


// ========================================================================= //
// Function Call: represents a function call with its arguments.             //
// ========================================================================= //

// Constructor: takes the name of the function and the list of arguments.
// Argument list can be NULL, in which case an empty one is created.
FcallNode::FcallNode(char *n, NodeList *args) {
  name = n;
  func = NULL;
  argv = args ? args : new NodeList();
}

// Destructor
FcallNode::~FcallNode() {
  free(name);
  while (!argv -> empty()) {
    AstNode *arg = argv -> front();
    argv -> pop_front();
    delete arg;
  }
  delete argv;
}

// Resolve: resolves all function arguments.
void FcallNode::resolve(Func *fn) {
  NodeList::iterator it = argv -> begin();
  for (; it != argv -> end(); ++it) {
    (*it) -> resolve(fn);
  }
}

// Evaluate: find the function and call it.
int  FcallNode::eval(int *env) {
  // (Lazy) Find the function
  if (!func) { func = FuncRegistry::find(name); }
  // Check for errors
  if (!func) { throw FIZ_UNDEF_FUNC; }
  if (argv -> size() != func -> argc) { throw FIZ_ARGNUM; }
  // Call the function
  return func -> call(argv, env);
}


// ========================================================================= //
// Environment Variable                                                      //
// ========================================================================= //

// Constructor: takes the name of the environment variable.
EnvarNode::EnvarNode(char *n) {
  name  = n;
  value = -1;
}

// Destructor
EnvarNode::~EnvarNode() {
  free(name);
}

// Resolve: resolves the variable to its value.
void EnvarNode::resolve(Func *fn) {
  char *str = getenv(name);
  char *tmp = str;
  // Make sure that the variable exists
  if (!str) { throw FIZ_UNDEF_VAR; }
  // Convert to integer...
  int val = strtol(str, &tmp, 10);
  // if this variable is not an integer, panic!
  if (*tmp != '\0' || val < 0) { throw FIZ_BAD_ENVAR; }
  value = val;
}

// Evaluate: return the value of the argument.
int  EnvarNode::eval(int *env) { return value; }
