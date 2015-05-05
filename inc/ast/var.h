#ifndef _AST_VAR_H_
#define _AST_VAR_H_

#include "node.h"

// ------------------------------------------------------------------------- //
// Variable: an identifier that refers to an integer value.                  //
// ------------------------------------------------------------------------- //
class VariableNode : public AstNode {
public:
  char *name;                          // Name of the variable
  int   index;                         // Index of the variable in arg list

  VariableNode(char*);                 // Constructor.
  ~VariableNode();                     // Destructor.

  void     resolve(Func*);             // Finds the index of variable.
  AstNode* eval(AstNode**);            // Fetches the value of the variable.
};

#endif
