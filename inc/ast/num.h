#ifndef _AST_NUM_H_
#define _AST_NUM_H_

#include "node.h"

// ------------------------------------------------------------------------- //
// Number: represents a positive integer value as entered into the FIZ.      //
// ------------------------------------------------------------------------- //
class NumNode : public AstNode {
public:
  int  value;                          // Value of the number node.

  NumNode(int);                        // Constructor.

  void     resolve(Func*);             // No-op for this class.
  AstNode* eval(AstNode**);            // Returns the value of the number node.

  void     print(int);
};

#endif
