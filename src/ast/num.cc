#include "num.h"

// ========================================================================= //
// Number: represents a positive integer value as entered into the FIZ.      //
// ========================================================================= //

// Constructor: takes the value of the number.
NumNode::NumNode(int value)  { this -> value = value; }

// Resolve: no-op.
void NumNode::resolve(Func *fn)   { }

// Evaluate: returns the value.
AstNode* NumNode::eval(AstNode *env[])  { 
  return this;
}


void NumNode::print(int fd) { dprintf(fd, "%d\n", this -> value); }
