#include "num.h"

// ========================================================================= //
// Number: represents a positive integer value as entered into the FIZ.      //
// ========================================================================= //

// Constructor: takes the value of the number.
NumNode::NumNode(int value)  { this -> value = value; }

// Resolve: no-op.
void NumNode::resolve(Func *fn)   { }

// Evaluate: returns the value.
int  NumNode::eval(int* env)      { return value; }
