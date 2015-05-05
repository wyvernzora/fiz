#ifndef _AST_LIST_H_
#define _AST_LIST_H_

#include "node.h"

// ------------------------------------------------------------------------- //
// List: represents a complex list of expressions.                           //
// ------------------------------------------------------------------------- //
class ListNode : public AstNode {
public:
  NodeList  *argv;                     // Elements of the list

  ListNode(NodeList*);                 // Constructor
  ~ListNode();                         // Destructor

  void resolve(Func*);                 // Resolves all argument nodes
  void eval(AstNode**);                // Evaluates the expression
}

#endif
