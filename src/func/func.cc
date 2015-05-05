// ------------------------------------------------------------------------- //
//                                                                           //
// CS252 Lab02 - FIZ Interpreter                                             //
// Copyright © 2015 Denis Luchkin-Zhou                                       //
//                                                                           //
// func.cc                                                                   //
// This file contains the logic for FIZ function structures, FIZ function    //
// registry and builtin functions.                                           //
//                                                                           //
// ------------------------------------------------------------------------- //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fiz/fiz.h"
#include "ast/node.h"
#include "func/func.h"

// ========================================================================= //
// Base Class for all functions.                                             //
// ========================================================================= //

// Call: no-op.
AstNode* Func::call(NodeList *args, AstNode *context[]) { return 0; }
