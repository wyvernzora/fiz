#include "ast/node.h"

// BUILTIN FUNCTIONS
AstNode* fiz_inc(NodeList*, AstNode**);          // (inc x)
AstNode* fiz_dec(NodeList*, AstNode**);          // (dec x)
AstNode* fiz_ifz(NodeList*, AstNode**);          // (ifz x y z)
AstNode* fiz_hlt(NodeList*, AstNode**);          // (halt)

AstNode* flip_list(NodeList*, AstNode**);        // (list x y)
AstNode* flip_head(NodeList*, AstNode**);        // (head x)
AstNode* flip_tail(NodeList*, AstNode**);        // (tail x)
AstNode* flip_ife(NodeList*, AstNode**);         // (ife x y z)

AstNode* flip_sys(NodeList*, AstNode**);         // (system x)
