#ifndef _FUNC_REGISTRY_H_
#define _FUNC_REGISTRY_H_

#include "func.h"

// ------------------------------------------------------------------------- //
// Comparator for builtin command map.                                       //
// ------------------------------------------------------------------------- //
struct StringComp :
  public std::binary_function<const char*, const char*, bool> {
    bool operator()(char const *a, char const *b) const {
      return strcmp(a, b) < 0;
    }
};

// ------------------------------------------------------------------------- //
// Shorthand for the function map.                                           //
// ------------------------------------------------------------------------- //
typedef std::map<char*, Func*, StringComp> FuncMap;

// ------------------------------------------------------------------------- //
// Registry that maps function names to definitions.                         //
// ------------------------------------------------------------------------- //
class FuncRegistry {
private:
  static FuncMap  map;                 // Map
public:
  static void  init();                 // Init. Adds builtin functnions
  static bool  reg(Func*);             // Registers a function.
  static Func* find(char*);            // Looks for a function by name.
};

#endif
