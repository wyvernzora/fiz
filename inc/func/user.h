#ifndef _FUNC_USER_H_
#define _FUNC_USER_H_

#include "func.h"

// ------------------------------------------------------------------------- //
// FIZ-scripted function definition.                                         //
// ------------------------------------------------------------------------- //
class UserFunc : public Func {
public:
  IdList           *args;              // Argument name list
  AstNode          *body;              // Body of the function (expr)

  UserFunc(char*, IdList*, AstNode*);  // Constructor
  ~UserFunc();                         // Destructor

  virtual AstNode* call(NodeList*, AstNode**);   // Calls the function
};

#endif
