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

    default: {
      return;
    }
  }
  return;
}
