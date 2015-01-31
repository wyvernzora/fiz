#include "ast.h"
#include "func.h"
#include "resolve.h"

void resolve(AstNode *node, Func *cf) {
  switch(node->type)
  {
    case INC_NODE: {
      resolve(node->argv[0], cf);
      return;
    }

    case DEC_NODE: {
      resolve(node->argv[0], cf);
      return;
    }

    case IFZ_NODE: {
      resolve(node->argv[0], cf);
      resolve(node->argv[1], cf);
      resolve(node->argv[2], cf);
      return;
    }

    case DEF_NODE: {
      resolve(node->argv[1], cf);
      return;
    }

    default: {
      return;
    }
  }
  return;
}
