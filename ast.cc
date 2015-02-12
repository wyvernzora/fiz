#include "trace.h"
#include "func.h"
#include "ast.h"

//AstNode::AstNode(void) { }
//AstNode::~AstNode(void) {

//}

void deleteNode(AstNode* node) {

  switch (node->type) {

    // LEAF: Identifier
    case ID_NODE: {
      TRACE("del ID_NODE [%s]\n", node->strValue);
      delete node->strValue; // Delete the identifier name
      delete node;
    }
    break;

    // LEAF: Number
    case NUMBER_NODE: {
      TRACE("del NUMBER_NODE [%d]\n", node->intValue);
      delete node;
    }
    break;

    case LIST_NODE: {
      TRACE("del LIST_NODE [%d]\n", node->argc);
      // Delete list contents
      for (int i = 0; i < node->argc; i++) { deleteNode(node->argv[i]); }
      delete node;
    }
    break;

    case FCALL_NODE: {

      TRACE("del FCALL_NODE [%s]\n", node->argv[0]->strValue);
      deleteNode(node->argv[0]); // Delete function name
      deleteNode(node->argv[1]); // Delete function arguments
      delete node; // Delete the node itself
    }
    break;
  }
}
