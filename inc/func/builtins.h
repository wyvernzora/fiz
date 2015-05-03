#include "ast/node.h"

// BUILTIN FUNCTIONS
int fiz_inc(NodeList*, int*);          // (inc x)
int fiz_dec(NodeList*, int*);          // (dec x)
int fiz_ifz(NodeList*, int*);          // (ifz x y z)
int fiz_hlt(NodeList*, int*);          // (halt)
