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

// FIZ-scripted Function
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

// Native Function
class NativeFunc : public Func {
private:
  int (*native)(AstNode**, int, int*);
public:
  NativeFunc(const char*, int, BuiltInFunc);
  ~NativeFunc(void);

  int call(AstNode**, int, int*);
};

// Function Registry
class BST {
public:
  char    *key;
  Func    *value;
  BST     *lnode;
  BST     *rnode;

  BST(Func*);
  int insert(BST*);
  BST* find(const char*);
};

class FuncRegistry {
private:
  int      count;
  BST     *root;
public:
  FuncRegistry(void) : count(0), root(NULL) { };
  int   reg(Func*);
  Func* find(const char*);
};

// BUILTIN FUNCTIONS
int fiz_inc(AstNode**, int, int*);
int fiz_dec(AstNode**, int, int*);
int fiz_ifz(AstNode**, int, int*);
int fiz_halt(AstNode**, int, int*);

#endif
