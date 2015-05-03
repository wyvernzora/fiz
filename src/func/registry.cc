// ========================================================================= //
// Function registry that maps function names to executable code.            //
// ========================================================================= //
#include "registry.h"
#include "builtins.h"
#include "native.h"

// Forward declaration
FuncMap FuncRegistry::map;

// Init: adds builtin functions to the map.
void FuncRegistry::init() {
  reg(new NativeFunc("inc",  1, fiz_inc));
  reg(new NativeFunc("dec",  1, fiz_dec));
  reg(new NativeFunc("ifz",  3, fiz_ifz));
  reg(new NativeFunc("halt", 0, fiz_hlt));
}

// Registers the function: returns true if successful; false otherwise.
bool FuncRegistry::reg(Func* fn) {
  if (map[fn -> name]) { return false; }
  map[fn -> name] = fn;
  return true;
}

// Retrieves a function with a given name. Returns NULL if not found.
Func* FuncRegistry::find(char* name) {
  return map[name];
}
