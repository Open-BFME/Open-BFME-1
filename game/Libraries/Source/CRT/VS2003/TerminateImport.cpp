// cl: /O2 /G7 /Oy /Ob1 /MD /D_CRTIMP=
// Native MSVCR71.dll!?terminate@@YAXXZ callable at B1 RVA009F7EDA.
// Public eh.h supplies terminate's actual cdecl/noreturn contract and pointer
// type. VC7.1 __identifier references only the actual strong undefined IAT
// symbol; C linkage supplies its ordinary leading underscore.
// B2 147fd3e CxxThrowExceptionImport.cpp is the compiler spelling donor.
#include <eh.h>

extern "C" {
extern terminate_function __identifier("_imp_?terminate@@YAXXZ");
}

void __cdecl terminate(void)
{
    __identifier("_imp_?terminate@@YAXXZ")();
}
