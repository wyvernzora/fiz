#include "var.h"
#include "func/user.h"

// ========================================================================= //
// Variable: an identifier that refers to an integer value.                  //
// ========================================================================= //

// Constructor: takes the name of the variable.
VariableNode::VariableNode(char* name) {
  this -> name = name;
  index = -1;
}

// Destructor
VariableNode::~VariableNode()     { free(name); }

// Resolve: finds the index of the variable in the function argument list.
void VariableNode::resolve(Func *fn) {
  UserFunc *ufn = (UserFunc*)fn;

  // if function definition is NULL, this variable shouldn't be here
  if (!fn) { throw FIZ_SYNTAX_ERROR; }

  // Look for the matching variable name
  int i    = 0,
      argc = ufn -> args -> size();
  for (; i < argc; i++) {
    if (!strcmp(ufn -> args -> at(i), name)) {
      index = i;
      break;
    }
  }

  // If still not found, the variable is undefined. panic.
  if (index < 0) { throw FIZ_UNDEF_VAR; }
}

// Evaluate: return the corresponding value from function argument list.
int  VariableNode::eval(int *env) { return env[index]; }
