// ------------------------------------------------------------------------- //
//                                                                           //
// CS252 Lab02 - FIZ Interpreter                                             //
// Copyright © 2015 Denis Luchkin-Zhou                                       //
//                                                                           //
// ast.h                                                                     //
// This file contains definitions of abstract syntax tree node definitions.  //
//                                                                           //
// ------------------------------------------------------------------------- //
#include <deque>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser/parser.h"
#include "fiz/fiz.h"

#ifndef AST_H
#define AST_H

// Forward declaration
class Func;

// ------------------------------------------------------------------------- //
// Abstract base class for all AST nodes.                                    //
// ------------------------------------------------------------------------- //
class AstNode {
public:
  virtual void resolve(Func*);         // Resolves the given node
  virtual int  eval(int*);             // Evaluates the given node and returns
                                       // the result.
};
typedef std::deque<AstNode*> NodeList;
typedef std::deque<char*>    IdList;

// ------------------------------------------------------------------------- //
// Number: represents a positive integer value as entered into the FIZ.      //
// ------------------------------------------------------------------------- //
class NumNode : public AstNode {
public:
  int  value;                          // Value of the number node.

  NumNode(int);                        // Constructor.

  void resolve(Func*);                 // No-op for this class.
  int  eval(int*);                     // Returns the value of the number node.
};

// ------------------------------------------------------------------------- //
// Variable: an identifier that refers to an integer value.                  //
// ------------------------------------------------------------------------- //
class VariableNode : public AstNode {
public:
  char *name;                          // Name of the variable
  int   index;                         // Index of the variable in arg list

  VariableNode(char*);                 // Constructor.
  ~VariableNode();                     // Destructor.

  void resolve(Func*);                 // Finds the index of variable.
  int  eval(int*);                     // Fetches the value of the variable.
};

// ------------------------------------------------------------------------- //
// Function Call: represents a function call with its arguments.             //
// ------------------------------------------------------------------------- //
class FcallNode : public AstNode {
public:
  char      *name;                     // Name of the function that is called
  Func      *func;                     // The resolved function definition
  NodeList  *argv;                     // List of arguments for the function

  FcallNode(char*, NodeList*);         // Constructor.
  ~FcallNode();                        // Destructor.

  void resolve(Func*);                 // Resolves all argument nodes.
  int  eval(int*);                     // Evaluates the function and returns
                                       // result of evaluation.
};

// ------------------------------------------------------------------------- //
// Environment Variable Node: an environment variable.                       //
// ------------------------------------------------------------------------- //
class EnvarNode : public AstNode {
public:
  char      *name;                     // Name of the environment variable.
  int        value;                    // Value of the environment variable.

  EnvarNode(char*);                    // Constructor.
  ~EnvarNode();                        // Destructor.

  void resolve(Func*);                 // Resolves variable to its value.
  int  eval(int*);                     // Returns the value.

};


#endif
