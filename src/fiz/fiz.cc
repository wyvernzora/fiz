// ------------------------------------------------------------------------- //
//                                                                           //
// CS252 Lab02 - FIZ Interpreter                                             //
// Copyright © 2015 Denis Luchkin-Zhou                                       //
//                                                                           //
// fiz.cc                                                                    //
// This file contains the logic for global functions, errors and public      //
// FIZ evaluation API.                                                       //
//                                                                           //
// ------------------------------------------------------------------------- //
#include <unistd.h>
#include <stdio.h>
#include "parser/parser.h"
#include "func/func.h"
#include "fiz/fiz.h"

// Forward declarations
bool            Fiz::_init;
std::deque<int> Fiz::_output;

// ------------------------------------------------------------------------- //
// Constructor. Creates a new Fiz interpreter wrapper instance.              //
// ------------------------------------------------------------------------- //
Fiz::Fiz() {
  if (!_init) {
    FuncRegistry::init();
    _init = true;
  }

  Parser::setPrompt(NULL);
  Parser::setOutput(Fiz::output);
}

// ------------------------------------------------------------------------- //
// Destructor. Detaches output buffer from FIZ and clears it.                //
// ------------------------------------------------------------------------- //
Fiz::~Fiz() {
  Parser::setOutput(NULL);
  while (!_output.empty()) { _output.pop_front(); }
}

// ------------------------------------------------------------------------- //
// Evaluates a FIZ expression and stores the output to buffer.               //
// Returns the number of integers outputted by the script.                   //
// ------------------------------------------------------------------------- //
int Fiz::eval(const char *script) {
  return eval(script, strlen(script));
}

// ------------------------------------------------------------------------- //
// Same as Fiz::eval(const char*).                                           //
// ------------------------------------------------------------------------- //
int Fiz::eval(const char *script, int count) {
  // Create input pipe
  int _pipe[2];
  if (pipe(_pipe) == -1) { throw FIZ_PIPE_FAIL; }
  // Save the number of output elements before evaluation
  int before = _output.size();
  // Write the evaluation script
  write(_pipe[1], script, count);
  close(_pipe[1]);
  // Set parser input and evaluate the expression
  Parser::setInput(_pipe[0]);
  fizparse();
  close(_pipe[0]);
  // Return the number of newly inserted elements
  return _output.size() - before;
}

// ------------------------------------------------------------------------- //
// Reads a maximum of `count` integers from output buffer to `buffer`, and   //
// returns the number of integers read.                                      //
// ------------------------------------------------------------------------- //
int Fiz::read(int *buffer, int count) {
  int c = 0;
  while (!_output.empty() && c++ < count) {
    *buffer++ = _output.front();
    _output.pop_front();
  }
  return c;
}

// ------------------------------------------------------------------------- //
// PRIVATE: Internal output function.                                        //
// ------------------------------------------------------------------------- //
void Fiz::output(int i) {
  _output.push_back(i);
}
