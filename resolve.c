#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "func.h"
#include "trace.h"
#include "resolve.h"

int resolve(AstNode *node, Func *cf) {
  switch(node->type)
  {
    case FCALL_NODE: {
      int      result = 1;
      AstNode *args   = node -> argv[1];

      // Resolve arguments
      for (int i = 0; i < args -> argc; i++)
        result &= resolve(args -> argv[i], cf);

      // Check if function exists

      return result;
    }

    case ID_NODE: {
      // Here we find the index of the argument in arg list
      // and assign that index to node->argc, since this node
      // will never have arguments and node->argc is always 0
      int   index = -1;
      char *name  = node->strValue;

      // Find the argument if there is a custom function
      if (cf) {
        for (int i = 0; i < cf->argc; i++) {
          if (!strcmp(cf->argv[i], name)) {
            index = i;
            break;
          }
        }
      }

      // Variable not found.. sad panda (Ｔ▽Ｔ)
      if (index < 0) {
        PANIC("Variable '%s' is undefined.\n", name);
        return 0;
      }

      // Just reusing an unused variable... (looking away
      node->index = index;
      return 1;
    }

    default: {
      return 1;
    }
  }
  return 1;
}
