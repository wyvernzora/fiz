#ifdef FUNC_H

// Function table
int  numFuncs;
Func* functions[MAX_FUNCTIONS + BUILTIN_FUNCTIONS];

#else

// Function table
extern int  numFuncs;
extern Func* functions[MAX_FUNCTIONS + BUILTIN_FUNCTIONS];

#endif
