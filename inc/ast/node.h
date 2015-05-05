#ifndef _AST_NODE_H_
#define _AST_NODE_H_

#include <deque>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "fiz/fiz.h"
#include "func/func.h"

// Forward declaration
class Func;

// ------------------------------------------------------------------------- //
// Abstract base class for all AST nodes.                                    //
// ------------------------------------------------------------------------- //
class AstNode {
public:
  virtual void     resolve(Func*);     // Resolves the given node
  virtual AstNode* eval(AstNode**);    // Evaluates the given node and returns
                                       // the result.
  virtual void     print(int);         // Prints the node value to fd.
};

#endif
