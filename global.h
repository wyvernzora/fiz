#ifdef FUNC_H

// Function table
FuncRegistry *functions;

#else

// Function table
class FuncRegistry;
extern FuncRegistry *functions;

#endif

// Uncomment this to enable functions with no arguments
//#define FUNC_ZERO_ARG
