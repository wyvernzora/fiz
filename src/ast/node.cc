#include <stdio.h>
#include "node.h"

// ========================================================================= //
// Abstract base class for all AST nodes.                                    //
// ========================================================================= //

// Resolve: no-op.
void AstNode::resolve(Func *fn)   { }

// Evaluate: no-op.
AstNode* AstNode::eval(AstNode *env[])  { return NULL; }

// Print: invalid.
void AstNode::print(int fd)       { throw FIZ_BAD_PRINT; }
