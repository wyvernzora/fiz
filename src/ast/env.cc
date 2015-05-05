#include "env.h"
#include "num.h"


// ========================================================================= //
// Environment Variable                                                      //
// ========================================================================= //

// Constructor: takes the name of the environment variable.
EnvarNode::EnvarNode(char *n) {
  name  = n;
  value = -1;
}

// Destructor
EnvarNode::~EnvarNode() {
  free(name);
}

// Resolve: resolves the variable to its value.
void EnvarNode::resolve(Func *fn) {
  char *str = getenv(name);
  char *tmp = str;
  // Make sure that the variable exists
  if (!str) { throw FIZ_UNDEF_VAR; }
  // Convert to integer...
  int val = strtol(str, &tmp, 10);
  // if this variable is not an integer, panic!
  if (*tmp != '\0' || val < 0) { throw FIZ_BAD_ENVAR; }
  value = val;
}

// Evaluate: return the value of the argument.
AstNode* EnvarNode::eval(AstNode *env[]) {
  return new NumNode(value);
}
