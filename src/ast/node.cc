#include <stdio.h>
#include "node.h"

#define INVALID_PRINT "Invalid invocation of AstNode::print()\n"

// ========================================================================= //
// Abstract base class for all AST nodes.                                    //
// ========================================================================= //

// Resolve: no-op.
void AstNode::resolve(Func *fn)   { }

// Evaluate: no-op.
AstNode* AstNode::eval(AstNode *env[])  { return NULL; }

// Print: invalid.
void AstNode::print(int fd)       { dprintf(fd, INVALID_PRINT); }
