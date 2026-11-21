// cl: /DNDEBUG /MD /O1
// Entire original MSVC7.1 atonexit.obj C member: _onexit38B, retained atexit18B,
// and both independent4B tentative COMMON definitions. Keep this TU in C:
// a C++ definition would force a joint8B BSS section and change native linkage.
// Original atonexit/crtexew CodeView proves void-cdecl callback-table globals;
// public stdlib.h independently supplies _onexit_t int-cdecl callback ABI.
// B2 147fd3e whole-member donor, reconciled to B1 native C type/storage context.
// No Microsoft CRT implementation source was read.
#include <stdlib.h>
typedef void (__cdecl *CrtExitCallback)(void);
CrtExitCallback *__onexitbegin;
CrtExitCallback *__onexitend;
extern _onexit_t (__cdecl *_imp___onexit)(_onexit_t);
_onexit_t __cdecl __dllonexit(_onexit_t, CrtExitCallback **, CrtExitCallback **);
_onexit_t __cdecl _onexit(_onexit_t callback)
{
    if (__onexitbegin == (CrtExitCallback *)-1)
        return _imp___onexit(callback);
    return __dllonexit(callback, &__onexitbegin, &__onexitend);
}
int __cdecl atexit(CrtExitCallback callback)
{
    return (_onexit((_onexit_t)callback) == 0) ? -1 : 0;
}
typedef char NativeCallbackPointerSize[(sizeof(CrtExitCallback) == 4) ? 1 : -1];
typedef char NativeExitTablePointerSize[(sizeof(__onexitbegin) == 4) ? 1 : -1];
