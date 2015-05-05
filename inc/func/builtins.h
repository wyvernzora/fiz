#include "ast/node.h"

// BUILTIN FUNCTIONS
AstNode* fiz_inc(NodeList*, AstNode**);          // (inc x)
AstNode* fiz_dec(NodeList*, AstNode**);          // (dec x)
AstNode* fiz_ifz(NodeList*, AstNode**);          // (ifz x y z)
AstNode* fiz_hlt(NodeList*, AstNode**);          // (halt)
