#include "trace.h"
#include "func.h"
#include "ast.h"

AstNode::AstNode(NodeType t) {
  type = t;
  argc = 0;
}
AstNode::~AstNode(void) {
  switch (type) {

    // LEAF: Identifier
    case ID_NODE: {
      TRACE("del ID_NODE [%s]\n", strValue);
      delete strValue; // Delete the identifier name
    }
    break;

    // LEAF: Number
    case NUMBER_NODE: {
      TRACE("del NUMBER_NODE [%d]\n", intValue);
    }
    break;

    case LIST_NODE: {
      TRACE("del LIST_NODE [%d]\n", argc);
      // Delete list contents
      for (int i = 0; i < argc; i++) { delete argv[i]; }
    }
    break;

    case FCALL_NODE: {
      TRACE("del FCALL_NODE [%s]\n", argv[0]->strValue);
      delete argv[0]; // Delete function name
      delete argv[1]; // Delete function arguments
    }
    break;
  }
}
