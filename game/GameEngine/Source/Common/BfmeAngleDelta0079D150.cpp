// cl: /DNDEBUG /MD /EHs-c-
// The retail x87 compare pops both operands and then conditionally adds to
// the already reloaded value. MSVC 7.1 does not reproduce that stack shape
// from equivalent C++ expressions, so this is the narrow x87 codegen seam.

extern float g_bfmeAngleTwoPi;

// ?bfmeDelta@@YAMMM@Z
float __cdecl bfmeDelta(float first, float second)
{
    __asm {
        fld dword ptr [esp + 4]
        fcomp dword ptr [esp + 8]
        fld dword ptr [esp + 4]
        fnstsw ax
        test ah, 5
        jp no_wrap
        fadd dword ptr [g_bfmeAngleTwoPi]
    no_wrap:
        fsub dword ptr [esp + 8]
    }
}
