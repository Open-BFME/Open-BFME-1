// cl: /O2 /MD /D_STLP_USE_STATIC_LIB
// stlport

// STLport 4.5.3 ios_base::_M_throw_failure (src/ios.cpp), retail 0x0083E8F0.
// BFME built ios.cpp without exception support, so the failure is reported
// on stderr instead of thrown: retail pushes the literal "ios failure"
// (0x0112EBAC) and &_iob[2], and calls MSVCR71 fputs. Its callers are the
// fstream constructors, through the inlined clear/_M_check_exception_mask.

#include <ios>
#include <stdio.h>

namespace _STL {
void ios_base::_M_throw_failure()
{
  const char *__arg = "ios failure";
  fputs(__arg, stderr);
}
}
