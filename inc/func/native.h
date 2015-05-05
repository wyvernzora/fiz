#ifndef _FUNC_NATIVE_H_
#define _FUNC_NATIVE_H_

#include "func.h"

// ------------------------------------------------------------------------- //
// Native function interface for FIZ scripts.                                //
// ------------------------------------------------------------------------- //
class NativeFunc : public Func {
private:
  BuiltInFunc native;                  // Pointer to function handler
public:

  NativeFunc(const char*, int,         // Constructor. Takes a name, number of
             BuiltInFunc);             // arguments and a pointer to handler

  AstNode* call(NodeList*, AstNode**); // Calls the function
};

#endif
