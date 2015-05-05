// ------------------------------------------------------------------------- //
//                                                                           //
// CS252 Lab02 - FIZ Interpreter                                             //
// Copyright © 2015 Denis Luchkin-Zhou                                       //
//                                                                           //
// func.h                                                                    //
// This file contains definitions for FIZ function structures, FIZ function  //
// registry and builtin functions.                                           //
//                                                                           //
// ------------------------------------------------------------------------- //
#include <map>
#include "ast/node.h"

#ifndef FUNC_H
#define FUNC_H

class AstNode;

typedef std::deque<AstNode*> NodeList;
typedef std::deque<char*>    IdList;

// ------------------------------------------------------------------------- //
// Shorthand for builtin function handler.                                   //
// ------------------------------------------------------------------------- //
typedef AstNode* (*BuiltInFunc)(NodeList*, AstNode**);

// ------------------------------------------------------------------------- //
// Base class for function definitions.                                      //
// ------------------------------------------------------------------------- //
class Func {
protected:
public:
  int               argc;              // Number of arguments
  char             *name;              // Name of the function

  virtual AstNode* call(NodeList*, AstNode**);   // Calls the function
};

#endif
