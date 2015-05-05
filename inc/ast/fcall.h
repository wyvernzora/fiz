#ifndef _AST_FCALL_H_
#define _AST_FCALL_H_

#include "node.h"

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

  void     resolve(Func*);             // Resolves all argument nodes.
  AstNode* eval(AstNode**);            // Evaluates the function and returns
                                       // result of evaluation.
};

#endif
