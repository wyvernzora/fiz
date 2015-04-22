#include "node.h"

// ========================================================================= //
// Abstract base class for all AST nodes.                                    //
// ========================================================================= //

// Resolve: no-op.
void AstNode::resolve(Func *fn)   { }

// Evaluate: no-op.
int  AstNode::eval(int *env)      { return 0; }
