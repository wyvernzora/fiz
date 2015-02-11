#ifndef TRACE_H
#define TRACE_H

#ifdef DEBUG

  #include <stdio.h>
  #define TRACE(...) fprintf(stderr, __VA_ARGS__);

#else

  #define TRACE(...)

#endif


#endif
