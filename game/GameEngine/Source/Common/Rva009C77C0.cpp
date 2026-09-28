// cl: /DNDEBUG /MD /O2
// ?rva009C77C0@@YAXPBX0PAX@Z
// Retail RVA 0x009C77C0..0x009C7CB8 (1272 bytes).
// Entry: int3 at 0x009C77BF; address loaded at 0x009B3B73 and stored in
// the dispatch table at 0x009B3B92. End: ret at 0x009C7CB7, then eight int3.
// Address-derived identity: the dispatcher proves a callable transform,
// but not its original source-level name.
//
// Multiply two 8x8 signed-word planes, apply an eight-lane fixed-point
// butterfly, transpose, and apply the butterfly again with rounding and
// a four-bit arithmetic shift. Intermediate paddw wraps; paddsw/psubsw
// saturate. This is the full-plane sibling of Rva009C7CC0ButterflySse.cpp.
//
// Codegen blocker: the equivalent SSE2-intrinsic implementation tested
// with VC7.1 /O2 /arch:SSE2 emitted 1646 bytes, a 16-byte realignment
// frame and 64 bytes of spills (retail has no SIMD stack frame). Explicit
// SIMD scheduling is required, as for the adjacent SSE transform. The
// compiler owns the outer EBX save/restore and return; no naked/emit body.
extern const unsigned short kRva012D8F40[56];
extern const unsigned short kRva012D8F20[8];

void __cdecl rva009C77C0(const void *coefficients, const void *multipliers,
                       void *output)
{
    __asm {
        // The inner EBX save makes the stack argument offsets 12/16/20.
        push ebx
        mov eax, dword ptr [esp + 0ch]
        mov ebx, dword ptr [esp + 010h]
        mov edx, dword ptr [esp + 014h]
        lea ecx, kRva012D8F40
        // Multiply all eight rows, retaining the low word of each product.
        movdqa xmm0, xmmword ptr [eax]
        movdqa xmm1, xmmword ptr [eax + 010h]
        pmullw xmm0, xmmword ptr [ebx]
        pmullw xmm1, xmmword ptr [ebx + 010h]
        movdqa xmm2, xmmword ptr [eax + 020h]
        movdqa xmm3, xmmword ptr [eax + 030h]
        pmullw xmm2, xmmword ptr [ebx + 020h]
        pmullw xmm3, xmmword ptr [ebx + 030h]
        movdqa xmmword ptr [edx], xmm0
        movdqa xmmword ptr [edx + 010h], xmm1
        movdqa xmm4, xmmword ptr [eax + 040h]
        movdqa xmm5, xmmword ptr [eax + 050h]
        pmullw xmm4, xmmword ptr [ebx + 040h]
        pmullw xmm5, xmmword ptr [ebx + 050h]
        movdqa xmmword ptr [edx + 020h], xmm2
        movdqa xmmword ptr [edx + 030h], xmm3
        movdqa xmm6, xmmword ptr [eax + 060h]
        movdqa xmm7, xmmword ptr [eax + 070h]
        pmullw xmm6, xmmword ptr [ebx + 060h]
        pmullw xmm7, xmmword ptr [ebx + 070h]
        movdqa xmmword ptr [edx + 040h], xmm4
        movdqa xmmword ptr [edx + 050h], xmm5
        movdqa xmmword ptr [edx + 060h], xmm6
        movdqa xmmword ptr [edx + 070h], xmm7
        // First fixed-point butterfly across eight rows.
        movdqa xmm2, xmmword ptr [edx + 030h]
        movdqa xmm6, xmmword ptr [ecx + 020h]
        movdqa xmm4, xmm2
        movdqa xmm7, xmmword ptr [edx + 050h]
        pmulhw xmm4, xmm6
        movdqa xmm1, xmmword ptr [ecx + 040h]
        pmulhw xmm6, xmm7
        movdqa xmm5, xmm1
        pmulhw xmm1, xmm2
        movdqa xmm3, xmmword ptr [edx + 010h]
        pmulhw xmm5, xmm7
        movdqa xmm0, xmmword ptr [ecx]
        paddw xmm4, xmm2
        paddw xmm6, xmm7
        paddw xmm2, xmm1
        movdqa xmm1, xmmword ptr [edx + 070h]
        paddw xmm7, xmm5
        movdqa xmm5, xmm0
        pmulhw xmm0, xmm3
        paddsw xmm4, xmm7
        pmulhw xmm5, xmm1
        movdqa xmm7, xmmword ptr [ecx + 060h]
        psubsw xmm6, xmm2
        paddw xmm0, xmm3
        pmulhw xmm3, xmm7
        movdqa xmm2, xmmword ptr [edx + 020h]
        pmulhw xmm7, xmm1
        paddw xmm5, xmm1
        movdqa xmm1, xmm2
        pmulhw xmm2, xmmword ptr [ecx + 010h]
        psubsw xmm3, xmm5
        movdqa xmm5, xmmword ptr [edx + 060h]
        paddsw xmm0, xmm7
        movdqa xmm7, xmm5
        psubsw xmm0, xmm4
        pmulhw xmm5, xmmword ptr [ecx + 010h]
        paddw xmm2, xmm1
        pmulhw xmm1, xmmword ptr [ecx + 050h]
        paddsw xmm4, xmm4
        paddsw xmm4, xmm0
        psubsw xmm3, xmm6
        paddw xmm5, xmm7
        paddsw xmm6, xmm6
        pmulhw xmm7, xmmword ptr [ecx + 050h]
        paddsw xmm6, xmm3
        movdqa xmmword ptr [edx + 010h], xmm4
        psubsw xmm1, xmm5
        movdqa xmm4, xmmword ptr [ecx + 030h]
        movdqa xmm5, xmm3
        pmulhw xmm3, xmm4
        paddsw xmm7, xmm2
        movdqa xmmword ptr [edx + 020h], xmm6
        movdqa xmm2, xmm0
        movdqa xmm6, xmmword ptr [edx]
        pmulhw xmm0, xmm4
        paddw xmm5, xmm3
        movdqa xmm3, xmmword ptr [edx + 040h]
        psubsw xmm5, xmm1
        paddw xmm2, xmm0
        psubsw xmm6, xmm3
        movdqa xmm0, xmm6
        pmulhw xmm6, xmm4
        paddsw xmm3, xmm3
        paddsw xmm1, xmm1
        paddsw xmm3, xmm0
        paddsw xmm1, xmm5
        pmulhw xmm4, xmm3
        paddw xmm6, xmm0
        psubsw xmm6, xmm2
        paddsw xmm2, xmm2
        movdqa xmm0, xmmword ptr [edx + 010h]
        paddsw xmm2, xmm6
        paddw xmm4, xmm3
        psubsw xmm2, xmm1
        paddsw xmm1, xmm1
        paddsw xmm1, xmm2
        psubsw xmm4, xmm7
        movdqa xmm3, xmmword ptr [edx + 020h]
        paddsw xmm7, xmm7
        movdqa xmmword ptr [edx + 020h], xmm2
        paddsw xmm7, xmm4
        movdqa xmmword ptr [edx + 010h], xmm1
        psubsw xmm4, xmm3
        paddsw xmm3, xmm3
        paddsw xmm3, xmm4
        psubsw xmm6, xmm5
        paddsw xmm5, xmm5
        paddsw xmm5, xmm6
        movdqa xmmword ptr [edx + 040h], xmm4
        movdqa xmmword ptr [edx + 030h], xmm3
        psubsw xmm7, xmm0
        paddsw xmm0, xmm0
        paddsw xmm0, xmm7
        movdqa xmmword ptr [edx + 060h], xmm6
        movdqa xmmword ptr [edx + 050h], xmm5
        movdqa xmmword ptr [edx + 070h], xmm7
        movdqa xmmword ptr [edx], xmm0
        // Transpose the 8x8 word block using word/dword/qword interleaves.
        movdqa xmm4, xmmword ptr [edx + 040h]
        movdqa xmm0, xmmword ptr [edx + 050h]
        movdqa xmm5, xmm4
        punpcklwd xmm4, xmm0
        punpckhwd xmm5, xmm0
        movdqa xmm6, xmmword ptr [edx + 060h]
        movdqa xmm0, xmmword ptr [edx + 070h]
        movdqa xmm7, xmm6
        punpcklwd xmm6, xmm0
        punpckhwd xmm7, xmm0
        movdqa xmm3, xmm4
        punpckldq xmm4, xmm6
        punpckhdq xmm3, xmm6
        movdqa xmmword ptr [edx + 060h], xmm3
        movdqa xmm6, xmm5
        punpckldq xmm5, xmm7
        punpckhdq xmm6, xmm7
        movdqa xmm0, xmmword ptr [edx]
        movdqa xmm1, xmmword ptr [edx + 010h]
        movdqa xmm7, xmm0
        punpcklwd xmm0, xmm1
        punpckhwd xmm7, xmm1
        movdqa xmm2, xmmword ptr [edx + 020h]
        movdqa xmm3, xmmword ptr [edx + 030h]
        movdqa xmm1, xmm2
        punpcklwd xmm2, xmm3
        punpckhwd xmm1, xmm3
        movdqa xmm3, xmm0
        punpckldq xmm0, xmm2
        punpckhdq xmm3, xmm2
        movdqa xmm2, xmm7
        punpckldq xmm2, xmm1
        punpckhdq xmm7, xmm1
        movdqa xmm1, xmm0
        punpcklqdq xmm0, xmm4
        punpckhqdq xmm1, xmm4
        movdqa xmmword ptr [edx], xmm0
        movdqa xmmword ptr [edx + 010h], xmm1
        movdqa xmm0, xmmword ptr [edx + 060h]
        movdqa xmm1, xmm3
        punpcklqdq xmm1, xmm0
        punpckhqdq xmm3, xmm0
        movdqa xmm4, xmm2
        punpcklqdq xmm4, xmm5
        punpckhqdq xmm2, xmm5
        movdqa xmmword ptr [edx + 020h], xmm1
        movdqa xmmword ptr [edx + 030h], xmm3
        movdqa xmmword ptr [edx + 040h], xmm4
        movdqa xmmword ptr [edx + 050h], xmm2
        movdqa xmm5, xmm7
        punpcklqdq xmm5, xmm6
        punpckhqdq xmm7, xmm6
        movdqa xmmword ptr [edx + 060h], xmm5
        movdqa xmmword ptr [edx + 070h], xmm7
        // Second butterfly on the transposed block.
        movdqa xmm2, xmmword ptr [edx + 030h]
        movdqa xmm6, xmmword ptr [ecx + 020h]
        movdqa xmm4, xmm2
        movdqa xmm7, xmmword ptr [edx + 050h]
        pmulhw xmm4, xmm6
        movdqa xmm1, xmmword ptr [ecx + 040h]
        pmulhw xmm6, xmm7
        movdqa xmm5, xmm1
        pmulhw xmm1, xmm2
        movdqa xmm3, xmmword ptr [edx + 010h]
        pmulhw xmm5, xmm7
        movdqa xmm0, xmmword ptr [ecx]
        paddw xmm4, xmm2
        paddw xmm6, xmm7
        paddw xmm2, xmm1
        movdqa xmm1, xmmword ptr [edx + 070h]
        paddw xmm7, xmm5
        movdqa xmm5, xmm0
        pmulhw xmm0, xmm3
        paddsw xmm4, xmm7
        pmulhw xmm5, xmm1
        movdqa xmm7, xmmword ptr [ecx + 060h]
        psubsw xmm6, xmm2
        paddw xmm0, xmm3
        pmulhw xmm3, xmm7
        movdqa xmm2, xmmword ptr [edx + 020h]
        pmulhw xmm7, xmm1
        paddw xmm5, xmm1
        movdqa xmm1, xmm2
        pmulhw xmm2, xmmword ptr [ecx + 010h]
        psubsw xmm3, xmm5
        movdqa xmm5, xmmword ptr [edx + 060h]
        paddsw xmm0, xmm7
        movdqa xmm7, xmm5
        psubsw xmm0, xmm4
        pmulhw xmm5, xmmword ptr [ecx + 010h]
        paddw xmm2, xmm1
        pmulhw xmm1, xmmword ptr [ecx + 050h]
        paddsw xmm4, xmm4
        paddsw xmm4, xmm0
        psubsw xmm3, xmm6
        paddw xmm5, xmm7
        paddsw xmm6, xmm6
        pmulhw xmm7, xmmword ptr [ecx + 050h]
        paddsw xmm6, xmm3
        movdqa xmmword ptr [edx + 010h], xmm4
        psubsw xmm1, xmm5
        movdqa xmm4, xmmword ptr [ecx + 030h]
        movdqa xmm5, xmm3
        pmulhw xmm3, xmm4
        paddsw xmm7, xmm2
        movdqa xmmword ptr [edx + 020h], xmm6
        movdqa xmm2, xmm0
        movdqa xmm6, xmmword ptr [edx]
        pmulhw xmm0, xmm4
        paddw xmm5, xmm3
        movdqa xmm3, xmmword ptr [edx + 040h]
        psubsw xmm5, xmm1
        paddw xmm2, xmm0
        psubsw xmm6, xmm3
        movdqa xmm0, xmm6
        pmulhw xmm6, xmm4
        paddsw xmm3, xmm3
        paddsw xmm1, xmm1
        paddsw xmm3, xmm0
        paddsw xmm1, xmm5
        pmulhw xmm4, xmm3
        paddw xmm6, xmm0
        psubsw xmm6, xmm2
        paddsw xmm2, xmm2
        movdqa xmm0, xmmword ptr [edx + 010h]
        paddsw xmm2, xmm6
        paddw xmm4, xmm3
        psubsw xmm2, xmm1
        // Round and scale the final signed words.
        paddsw xmm2, xmmword ptr [kRva012D8F20]
        paddsw xmm1, xmm1
        paddsw xmm1, xmm2
        psraw xmm2, 4
        psubsw xmm4, xmm7
        psraw xmm1, 4
        movdqa xmm3, xmmword ptr [edx + 020h]
        paddsw xmm7, xmm7
        movdqa xmmword ptr [edx + 020h], xmm2
        paddsw xmm7, xmm4
        movdqa xmmword ptr [edx + 010h], xmm1
        psubsw xmm4, xmm3
        paddsw xmm4, xmmword ptr [kRva012D8F20]
        paddsw xmm3, xmm3
        paddsw xmm3, xmm4
        psraw xmm4, 4
        psubsw xmm6, xmm5
        psraw xmm3, 4
        paddsw xmm6, xmmword ptr [kRva012D8F20]
        paddsw xmm5, xmm5
        paddsw xmm5, xmm6
        psraw xmm6, 4
        movdqa xmmword ptr [edx + 040h], xmm4
        psraw xmm5, 4
        movdqa xmmword ptr [edx + 030h], xmm3
        psubsw xmm7, xmm0
        paddsw xmm7, xmmword ptr [kRva012D8F20]
        paddsw xmm0, xmm0
        paddsw xmm0, xmm7
        psraw xmm7, 4
        movdqa xmmword ptr [edx + 060h], xmm6
        psraw xmm0, 4
        movdqa xmmword ptr [edx + 050h], xmm5
        movdqa xmmword ptr [edx + 070h], xmm7
        movdqa xmmword ptr [edx], xmm0
        pop ebx
    }
}
