// ========================================================================= //
// Function scripted in FIZ.                                                 //
// ========================================================================= //

#include "user.h"

// Constructor. Takes a name, list of arguments and an AST node body.
UserFunc::UserFunc(char *name, IdList *args, AstNode *body) {
  this -> name = name;
  this -> args = args ? args : new IdList();
  this -> argc = args ? args -> size() : 0;
  this -> body = body;
}

// Destructor.
UserFunc::~UserFunc() {
  free(name);
  while (!args -> empty()) {
    char *arg = args -> front();
    args -> pop_front();
    free(arg);
  }
  if (body) { delete body; }
}

// Call: creates a context from arguments and evaluates the function body AST.
// Takes a list of AST nodes as arguments, and the parent context.
AstNode* UserFunc::call(NodeList *args, AstNode *context[]) {
  // Check the number of arguments
  int argc  = args -> size();
  if (argc != this -> argc) { throw FIZ_ARGNUM; }
  // Evaluate all arguments
  AstNode **params = new AstNode*[argc];
  for (int i = 0; i < argc; i++) {
    params[i] = args -> at(i) -> eval(context);
  }
  // Evaluate the function body AST
  AstNode *result = body -> eval(params);
  delete params;
  return result;
}
