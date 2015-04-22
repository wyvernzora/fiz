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
#include "ast/ast.h"

#ifndef FUNC_H
#define FUNC_H

// ------------------------------------------------------------------------- //
// Shorthand for builtin function handler.                                   //
// ------------------------------------------------------------------------- //
typedef int (*BuiltInFunc)(NodeList*, int*);

// ------------------------------------------------------------------------- //
// Base class for function definitions.                                      //
// ------------------------------------------------------------------------- //
class Func {
protected:
public:
  int               argc;              // Number of arguments
  char             *name;              // Name of the function

  virtual int call(NodeList*, int*);   // Calls the function and returns result
};

// ------------------------------------------------------------------------- //
// FIZ-scripted function definition.                                         //
// ------------------------------------------------------------------------- //
class UserFunc : public Func {
public:
  IdList           *args;              // Argument name list
  AstNode          *body;              // Body of the function (expr)

  UserFunc(char*, IdList*, AstNode*);  // Constructor
  ~UserFunc();                         // Destructor

  virtual int call(NodeList*, int*);   // Calls the function
};

// ------------------------------------------------------------------------- //
// Native function interface for FIZ scripts.                                //
// ------------------------------------------------------------------------- //
class NativeFunc : public Func {
private:
  BuiltInFunc native;                  // Pointer to function handler
public:

  NativeFunc(const char*, int,         // Constructor. Takes a name, number of
             BuiltInFunc);             // arguments and a pointer to handler

  int call(NodeList*, int*);           // Calls the function
};


// ------------------------------------------------------------------------- //
// Comparator for builtin command map.                                       //
// ------------------------------------------------------------------------- //
struct StringComp :
  public std::binary_function<const char*, const char*, bool> {
    bool operator()(char const *a, char const *b) const {
      return strcmp(a, b) < 0;
    }
};

// ------------------------------------------------------------------------- //
// Shorthand for the function map.                                           //
// ------------------------------------------------------------------------- //
typedef std::map<char*, Func*, StringComp> FuncMap;

// ------------------------------------------------------------------------- //
// Registry that maps function names to definitions.                         //
// ------------------------------------------------------------------------- //
class FuncRegistry {
private:
  static FuncMap  map;                 // Map
public:
  static void  init();                 // Init. Adds builtin functnions
  static bool  reg(Func*);             // Registers a function.
  static Func* find(char*);            // Looks for a function by name.
};

// BUILTIN FUNCTIONS
int fiz_inc(NodeList*, int*);          // (inc x)
int fiz_dec(NodeList*, int*);          // (dec x)
int fiz_ifz(NodeList*, int*);          // (ifz x y z)
int fiz_hlt(NodeList*, int*);          // (halt)

#endif
