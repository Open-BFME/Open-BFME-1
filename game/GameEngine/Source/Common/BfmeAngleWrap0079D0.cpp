// cl: /DNDEBUG /MD /EHs-c-

extern void __cdecl ji_009f70cc(void);
// Retail VA 0x01075350 is four readonly zero bytes. Both x87 comparisons
// below use DWORD operands; no EA variable name is proven.
extern const float g_rva01075350 = 0.0f;
extern float g_bfmeAngleTwoPi;
extern double g_bfmeAngleTwoPiDouble;

// ?Rva0079D0A0@@YANM@Z
double __cdecl Rva0079D0A0(float angle)
{
    __asm {
        fld dword ptr [esp + 4]
        fcomp dword ptr [g_rva01075350]
        fnstsw ax
        test ah, 5
        jp positive

        fld dword ptr [esp + 4]
        fchs
        fld qword ptr [g_bfmeAngleTwoPiDouble]
        call ji_009f70cc
        fsubr dword ptr [g_bfmeAngleTwoPi]
        ret

    positive:
        fld dword ptr [esp + 4]
        fld qword ptr [g_bfmeAngleTwoPiDouble]
        call ji_009f70cc
    }
}

// ?Rva0079D0F0@@YANPAX@Z
double __cdecl Rva0079D0F0(void *pair)
{
    __asm {
        mov eax, dword ptr [esp + 4]
        fld dword ptr [eax + 4]
        fld dword ptr [eax]
        fpatan
        fst dword ptr [esp + 4]
        fcomp dword ptr [g_rva01075350]
        fnstsw ax
        test ah, 5
        jp positive_pair

        fld dword ptr [esp + 4]
        fchs
        fld qword ptr [g_bfmeAngleTwoPiDouble]
        call ji_009f70cc
        fsubr dword ptr [g_bfmeAngleTwoPi]
        ret

    positive_pair:
        fld dword ptr [esp + 4]
        fld qword ptr [g_bfmeAngleTwoPiDouble]
        call ji_009f70cc
    }
}
