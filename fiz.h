// ------------------------------------------------------------------------- //
//                                                                           //
// CS252 Lab02 - FIZ Interpreter                                             //
// Copyright © 2015 Denis Luchkin-Zhou                                       //
//                                                                           //
// fiz.h                                                                     //
// This file contains definitions for global functions, errors and public    //
// FIZ evaluation API.                                                       //
//                                                                           //
// ------------------------------------------------------------------------- //
#ifndef FIZ_H_
#define FIZ_H_

// ------------------------------------------------------------------------- //
// FIZ error struct.                                                         //
// ------------------------------------------------------------------------- //
typedef struct FIZ_ERR {
  int         code;
  const char *message;

  static FIZ_ERR create(int c, const char *m) {
    FIZ_ERR error;
    error.code    = c;
    error.message = m;
    return error;
  }
} FizError;

// ------------------------------------------------------------------------- //
// FIZ global error flags.                                                   //
// ------------------------------------------------------------------------- //
#define FIZ_ERR(c, m)   (FizError::create(c, m))
#define FIZ_ERRNO(err)  (err.code)
#define FIZ_STRERR(err) (err.message)

// ------------------------------------------------------------------------- //
// FIZ error codes and their respective descriptions.                        //
// ------------------------------------------------------------------------- //
#define FIZ_INCLUDE_FAIL     FIZ_ERR(900, "Failed to open imported file.")
#define FIZ_SYNTAX_ERROR     FIZ_ERR(901, "Syntax error.")
#define FIZ_DUP_FUNC         FIZ_ERR(902, "Function is already defined.")
#define FIZ_UNDEF_FUNC       FIZ_ERR(903, "Function is not defined.")
#define FIZ_ARGNUM           FIZ_ERR(904, "Unexpected number of arguments.")
#define FIZ_DEC_ZERO         FIZ_ERR(905, "Attempt to (dec 0).")
#define FIZ_HALT             FIZ_ERR(906, "Halted.")
#define FIZ_UNDEF_VAR        FIZ_ERR(907, "Variable is not defined.")

// ------------------------------------------------------------------------- //
// Called to start the YACC parsing process.                                 //
// ------------------------------------------------------------------------- //
int  yylex();

// ------------------------------------------------------------------------- //
// Handles the YACC errors.                                                  //
// ------------------------------------------------------------------------- //
void yyerror(const char*);

// ------------------------------------------------------------------------- //
// Prints an input prompt (only when in TTY mode).                           //
// ------------------------------------------------------------------------- //
void prompt(void);

// ------------------------------------------------------------------------- //
// Outputs the result of a signle FIZ statement.                             //
// ------------------------------------------------------------------------- //
void output(int);

// ------------------------------------------------------------------------- //
// YACC parse function definition.                                           //
// ------------------------------------------------------------------------- //
int yyparse(void);

#endif
