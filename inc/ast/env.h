#ifndef _AST_ENV_H_
#define _AST_ENV_H_

#include "node.h"

// ------------------------------------------------------------------------- //
// Environment Variable Node: an environment variable.                       //
// ------------------------------------------------------------------------- //
class EnvarNode : public AstNode {
public:
  char      *name;                     // Name of the environment variable.
  int        value;                    // Value of the environment variable.

  EnvarNode(char*);                    // Constructor.
  ~EnvarNode();                        // Destructor.

  void     resolve(Func*);             // Resolves variable to its value.
  AstNode* eval(AstNode**);            // Returns the value.

};

#endif
