// cl: /O1 /Ob1 /MD /D_CRTIMP=
// Native libc fp8.obj: complete18B _setdefaultprecision. Startup's original
// crtexew.obj REL32 names this C entry. float.h's declaration is local
// (no dllimport); the call uses the unchanged original native CODE import.
// B2 147fd3e DefaultPrecision.cpp donor; B1 original member independently checked.
// No CRT implementation source was read.
#include <float.h>
extern "C" void __cdecl _setdefaultprecision()
{
    _controlfp(_PC_53, _MCW_PC);
}
