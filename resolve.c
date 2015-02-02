#include "ast.h"
#include "func.h"
#include "resolve.h"

void resolve(AstNode *node, Func *cf) {
  switch(node->type)
  {
    case FCALL_NODE: {
      // Resolve arguments
      AstNode *args = node -> argv[1];
      for (int i = 0; i < args -> argc; i++) {
        resolve(args -> argv[i], cf);
      }
      return;
    }

    case ID_NODE: {
      // Here we find the index of the argument in arg list
      // and assign that index to node->argc, since this node
      // will never have arguments and node->argc is always 0
      char* name = node->strValue;
      int index = -1;
      if (cf) {
        for (int i = 0; i < cf->argc; i++) {
          if (!strcmp(cf->argv[i], name)) {
            index = i;
            break;
          }
        }
      }

      if (index < 0) {
        fprintf(stderr, "Variable '%s' is undefined.\n", name);
        exit(1);
      }

      node->argc = index;
    }

    default: {
      return;
    }
  }
  return;
}
