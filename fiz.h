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

#include <deque>

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
#define FIZ_PIPE_FAIL        FIZ_ERR(908, "Pipe creation failed.")


// ------------------------------------------------------------------------- //
// FIZ Interactive Prompt Handler.                                           //
// ------------------------------------------------------------------------- //
typedef void (*PromptHandler)(void);

// ------------------------------------------------------------------------- //
// Public FIZ parser API.                                                    //
// ------------------------------------------------------------------------- //
class Fiz {
private:
  static bool            _init;        // Indicates whether FIZ is initialized.
  static std::deque<int> _output;      // Output buffer. Sort of.

  static void  output(int);            // Internal output function.

public:

  Fiz();                               // New FIZ instance using builtin pipes.
  ~Fiz();                              // Destructor.

  // Interpreter I/O
  int  eval(const char*);              // Evaluates script.
  int  eval(const char*, int);         // Evaluates script.
  int  read(int*, int);                // Reads script output.
};

#endif
