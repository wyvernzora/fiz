// ========================================================================= //
//                                                                           //
// FIZ Interpreter                                                           //
// Author: Denis Luchkin-Zhou                                                //
//                                                                           //
// ========================================================================= //
#include "ast.h"

#ifndef FUNC_H
#define FUNC_H

// Maximum number of function definitions the interpreter allow
#define MAX_FUNCTIONS 1000
#define BUILTIN_FUNCTIONS 4

// Builtin function signature
typedef int (*BuiltInFunc)(AstNode**, int, int*);

// Function type
class Func {
public:
  int               argc;
  char             *name;
  char             *argv[MAX_ARGUMENTS];  // Argument name list
  AstNode          *body;                 // Body of the function (expr)

  Func();
  Func(char*);
  ~Func(void);

  virtual int call(AstNode**, int, int*);
};

class NativeFunc : public Func {
private:
  int (*native)(AstNode**, int, int*);
public:
  NativeFunc(const char*, int, BuiltInFunc);
  ~NativeFunc(void);

  int call(AstNode**, int, int*);
};

// Find a function and return it's metadata
Func * find_function(char*);

// Define a function
void registerFunction(Func*);

// Call a function
int call_function(char*, AstNode**, int, int*);

// Determines whether a function is a builtin function
BuiltInFunc find_builtin_func(char*);

// BUILTIN FUNCTIONS
int fiz_inc(AstNode**, int, int*);
int fiz_dec(AstNode**, int, int*);
int fiz_ifz(AstNode**, int, int*);
int fiz_halt(AstNode**, int, int*);


#endif
