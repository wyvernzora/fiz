// ========================================================================= //
//                                                                           //
// FIZ Interpreter                                                           //
// Author: Denis Luchkin-Zhou                                                //
//                                                                           //
// ========================================================================= //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "ast.h"

#ifndef RESOLVE_H
#define RESOLVE_H

// Resolve the usage of functions and arguments in an expression
void resolve(AstNode *node, Func *cf);

#endif
