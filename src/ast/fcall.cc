#include "fcall.h"

// ========================================================================= //
// Function Call: represents a function call with its arguments.             //
// ========================================================================= //

// Constructor: takes the name of the function and the list of arguments.
// Argument list can be NULL, in which case an empty one is created.
FcallNode::FcallNode(char *n, NodeList *args) {
  name = n;
  func = NULL;
  argv = args ? args : new NodeList();
}

// Destructor
FcallNode::~FcallNode() {
  free(name);
  while (!argv -> empty()) {
    AstNode *arg = argv -> front();
    argv -> pop_front();
    delete arg;
  }
  delete argv;
}

// Resolve: resolves all function arguments.
void FcallNode::resolve(Func *fn) {
  NodeList::iterator it = argv -> begin();
  for (; it != argv -> end(); ++it) {
    (*it) -> resolve(fn);
  }
}

// Evaluate: find the function and call it.
int  FcallNode::eval(int *env) {
  // (Lazy) Find the function
  if (!func) { func = FuncRegistry::find(name); }
  // Check for errors
  if (!func) { throw FIZ_UNDEF_FUNC; }
  if (argv -> size() != func -> argc) { throw FIZ_ARGNUM; }
  // Call the function
  return func -> call(argv, env);
}
