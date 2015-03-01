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

#define OUT_BUFFER_SIZE 16

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
// YACC parse function definition.                                           //
// ------------------------------------------------------------------------- //
int yyparse(void);

// ------------------------------------------------------------------------- //
// Public FIZ parser API.                                                    //
// ------------------------------------------------------------------------- //
class Fiz {
private:
  char *_prompt;                       // Prompt string (when input is TTY).
  int   _out_sz;                       // FIZ output buffer capacity.
  int  *_out_pt;                       // FIZ output buffer.
  int  *_out_wr;                       // FIZ output write pointer.
  int  *_out_rd;                       // FIZ output read pointer.

  int   _pipe[2];                      // Builtin pipe if no input supplied.

  void  _prompt();
  void  _output(int);

public:

  Fiz();                               // New FIZ instance using builtin pipes.
  Fiz(int);                            // New FIZ instance that reads from fd.
  ~Fiz();

  // Interpreter I/O
  int  write(char*);
  int  write(char*, int);
  int  read(int*, int);

  // Setup
  void setPrompt(const char*);
};

#endif
