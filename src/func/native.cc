// ========================================================================= //
// Native function that is exposed to the FIZ runtime.                       //
// ========================================================================= //
#include "native.h"

// Constructor. Takes a function name, number of arguments and a pointer to
// the function to expose.
NativeFunc::NativeFunc(const char *name, int argc, BuiltInFunc native) {
  this->argc = argc;
  this->name = strdup(name);
  this->native = native;
}

// Call: passes arguments to the native handler.
int NativeFunc::call(NodeList *args, int *env) {
  return (*native)(args, env);
}
