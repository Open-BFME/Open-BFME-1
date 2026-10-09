// ?Rva009B6D80@@YAXPAURva009B6D80Context@@PBEPAEHIIPBI@Z
// partial score=0.9986 date=2026-10-09
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// MMX edge kernels with scalar threshold selection and variance accumulation.
// cl: /O2 /Z7 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
struct Rva009B6D80Context
{
    unsigned char m_pad00[0x24];
    const unsigned int *m_24;
    unsigned int *m_28;
};
static const unsigned short packedThree[4] = {3, 3, 3, 3};
static const unsigned short packedFour[4] = {4, 4, 4, 4};

// Open BFME 2: Code/GameEngine/Source/Common/Rva001CA000Vp6WideAccum.cpp
void __cdecl Rva009B6D80(Rva009B6D80Context *context, const unsigned char *source,
    unsigned char *destination, int stride, unsigned int count, unsigned int start,
    const unsigned int *strength)
{
    const unsigned char *sourceWalk = source;
    unsigned int index = start;
    unsigned char *destinationWalk = destination;
    __declspec(align(16)) unsigned short leftHigh[4];
    __declspec(align(16)) unsigned short rightHigh[4];
    __declspec(align(16)) unsigned short leftLow[4];
    __declspec(align(16)) unsigned short rightLow[4];
    __declspec(align(16)) unsigned short limit[4];
    unsigned int end = count + start;
    __declspec(align(16)) unsigned short varianceLimit[4];
    __declspec(align(16)) unsigned short samples[80];
    __declspec(align(16)) unsigned short filtered[64];
    unsigned int tableIndex = end;

    for (; index < end; ++index, ++tableIndex)
    {
        unsigned int value = strength[context->m_24[tableIndex]];
        if (value > 3)
        {
            limit[0] = (unsigned short)value;
            limit[1] = (unsigned short)value;
            limit[2] = (unsigned short)value;
            limit[3] = (unsigned short)value;
            __asm
            {
            push eax
            push ebp
            push ecx
            push edx
            push esi
            push edi
            movq mm0, qword ptr limit
            movq mm1, qword ptr packedThree
            pmullw mm1, mm0
            pmullw mm1, mm0
            psrlw mm1, 5
            movq qword ptr varianceLimit, mm1
            mov eax, dword ptr sourceWalk
            xor edx, edx
            lea esi, filtered
            lea edi, samples
            mov ecx, dword ptr stride
            pxor mm7, mm7
            sub edx, ecx
            lea eax, [eax + edx*4]
            movq mm0, qword ptr [eax + edx]
            movq mm1, mm0
            punpcklbw mm0, mm7
            movq mm2, qword ptr [eax]
            movq mm3, mm2
            punpckhbw mm1, mm7
            movq qword ptr [edi], mm0
            punpcklbw mm2, mm7
            punpckhbw mm3, mm7
            movq qword ptr [edi + 8], mm1
            movq mm4, qword ptr [eax + ecx]
            movq qword ptr [edi + 0x10], mm2
            movq qword ptr [edi + 0x18], mm3
            movq mm5, mm4
            punpcklbw mm4, mm7
            movq mm0, qword ptr [eax + ecx*2]
            punpckhbw mm5, mm7
            movq mm1, mm0
            movq qword ptr [edi + 0x20], mm4
            punpcklbw mm0, mm7
            lea eax, [eax + ecx*4]
            movq qword ptr [edi + 0x28], mm5
            punpckhbw mm1, mm7
            movq mm2, qword ptr [eax + edx]
            movq qword ptr [edi + 0x30], mm0
            movq mm3, mm2
            punpcklbw mm2, mm7
            movq qword ptr [edi + 0x38], mm1
            punpckhbw mm3, mm7
            movq mm4, qword ptr [eax]
            movq qword ptr [edi + 0x40], mm2
            movq mm5, mm4
            movq qword ptr [edi + 0x48], mm3
            punpcklbw mm4, mm7
            punpckhbw mm5, mm7
            movq mm0, qword ptr [eax + ecx]
            movq qword ptr [edi + 0x50], mm4
            movq mm1, mm0
            movq qword ptr [edi + 0x58], mm5
            punpcklbw mm0, mm7
            punpckhbw mm1, mm7
            movq mm2, qword ptr [eax + ecx*2]
            lea eax, [eax + ecx*4]
            movq mm3, mm2
            movq qword ptr [edi + 0x60], mm0
            punpcklbw mm2, mm7
            punpckhbw mm3, mm7
            movq mm4, qword ptr [eax + edx]
            movq qword ptr [edi + 0x68], mm1
            movq mm5, mm4
            punpcklbw mm4, mm7
            movq qword ptr [edi + 0x70], mm2
            movq qword ptr [edi + 0x78], mm3
            movq mm0, qword ptr [eax]
            punpckhbw mm5, mm7
            movq mm1, mm0
            movq qword ptr [edi + 0x80], mm4
            punpcklbw mm0, mm7
            punpckhbw mm1, mm7
            movq qword ptr [edi + 0x88], mm5
            movq qword ptr [edi + 0x90], mm0
            movq qword ptr [edi + 0x98], mm1
            pcmpeqw mm3, mm3
            psllw mm3, 0xf
            psrlw mm3, 8
            movq mm2, qword ptr [edi + 0x10]
            movq mm6, qword ptr [edi + 0x50]
            psubw mm2, mm3
            psubw mm6, mm3
            movq mm0, mm2
            movq mm4, mm6
            pmullw mm2, mm2
            pmullw mm6, mm6
            movq mm1, mm2
            movq mm5, mm6
            movq mm2, qword ptr [edi + 0x20]
            movq mm6, qword ptr [edi + 0x60]
            psubw mm2, mm3
            psubw mm6, mm3
            paddw mm0, mm2
            paddw mm4, mm6
            pmullw mm2, mm2
            pmullw mm6, mm6
            paddw mm1, mm2
            paddw mm5, mm6
            movq mm2, qword ptr [edi + 0x30]
            movq mm6, qword ptr [edi + 0x70]
            psubw mm2, mm3
            psubw mm6, mm3
            paddw mm0, mm2
            paddw mm4, mm6
            pmullw mm2, mm2
            pmullw mm6, mm6
            paddw mm1, mm2
            paddw mm5, mm6
            movq mm2, qword ptr [edi + 0x40]
            movq mm6, qword ptr [edi + 0x80]
            psubw mm2, mm3
            psubw mm6, mm3
            paddw mm0, mm2
            paddw mm4, mm6
            pmullw mm2, mm2
            pmullw mm6, mm6
            paddw mm1, mm2
            paddw mm5, mm6
            movq mm7, mm3
            psrlw mm7, 7
            movq mm2, mm0
            movq mm6, mm4
            paddw mm0, mm7
            paddw mm4, mm7
            psraw mm2, 1
            psraw mm6, 1
            psraw mm0, 1
            psraw mm4, 1
            pmullw mm2, mm0
            pmullw mm6, mm4
            psubw mm1, mm2
            psubw mm5, mm6
            movq mm7, qword ptr varianceLimit
            movq mm2, mm1
            movq mm6, mm5
            movq qword ptr leftLow, mm1
            movq qword ptr rightLow, mm5
            psubw mm1, mm7
            psubw mm5, mm7
            psraw mm2, 0xf
            psraw mm6, 0xf
            psraw mm1, 0xf
            psraw mm5, 0xf
            movq mm7, qword ptr [edi + 0x40]
            pandn mm2, mm1
            pandn mm6, mm5
            movq mm4, qword ptr [edi + 0x50]
            pand mm6, mm2
            movq mm2, mm7
            psubusw mm7, mm4
            psubusw mm4, mm2
            por mm7, mm4
            psubw mm7, qword ptr limit
            psraw mm7, 0xf
            pand mm7, mm6
            add edi, 8
            movq mm2, qword ptr [edi + 0x10]
            movq mm6, qword ptr [edi + 0x50]
            psubw mm2, mm3
            psubw mm6, mm3
            movq mm0, mm2
            movq mm4, mm6
            pmullw mm2, mm2
            pmullw mm6, mm6
            movq mm1, mm2
            movq mm5, mm6
            movq mm2, qword ptr [edi + 0x20]
            movq mm6, qword ptr [edi + 0x60]
            psubw mm2, mm3
            psubw mm6, mm3
            paddw mm0, mm2
            paddw mm4, mm6
            pmullw mm2, mm2
            pmullw mm6, mm6
            paddw mm1, mm2
            paddw mm5, mm6
            movq mm2, qword ptr [edi + 0x30]
            movq mm6, qword ptr [edi + 0x70]
            psubw mm2, mm3
            psubw mm6, mm3
            paddw mm0, mm2
            paddw mm4, mm6
            pmullw mm2, mm2
            pmullw mm6, mm6
            paddw mm1, mm2
            paddw mm5, mm6
            movq mm2, qword ptr [edi + 0x40]
            movq mm6, qword ptr [edi + 0x80]
            psubw mm2, mm3
            psubw mm6, mm3
            paddw mm0, mm2
            paddw mm4, mm6
            pmullw mm2, mm2
            pmullw mm6, mm6
            paddw mm1, mm2
            paddw mm5, mm6
            psrlw mm3, 7
            movq mm2, mm0
            movq mm6, mm4
            paddw mm0, mm3
            paddw mm4, mm3
            psraw mm2, 1
            psraw mm6, 1
            psraw mm0, 1
            psraw mm4, 1
            pmullw mm2, mm0
            pmullw mm6, mm4
            psubw mm1, mm2
            psubw mm5, mm6
            movq qword ptr leftHigh, mm1
            movq qword ptr rightHigh, mm5
            movq mm3, qword ptr varianceLimit
            movq mm2, mm1
            movq mm6, mm5
            psubw mm1, mm3
            psubw mm5, mm3
            psraw mm2, 0xf
            psraw mm6, 0xf
            psraw mm1, 0xf
            psraw mm5, 0xf
            movq mm0, qword ptr [edi + 0x40]
            pandn mm2, mm1
            pandn mm6, mm5
            movq mm4, qword ptr [edi + 0x50]
            pand mm6, mm2
            movq mm2, mm0
            psubusw mm0, mm4
            psubusw mm4, mm2
            por mm0, mm4
            psubw mm0, qword ptr limit
            psraw mm0, 0xf
            pand mm0, mm6
            sub edi, 8
            movq mm5, qword ptr [edi]
            movq mm4, qword ptr [edi + 0x10]
            movq mm3, mm4
            movq mm6, mm5
            psubusw mm4, mm6
            psubusw mm5, mm3
            por mm4, mm5
            psubw mm4, qword ptr limit
            psraw mm4, 0xf
            movq mm1, mm4
            pand mm4, mm6
            pandn mm1, mm3
            por mm1, mm4
            movq mm4, qword ptr [edi + 0x80]
            movq mm5, qword ptr [edi + 0x90]
            movq mm3, mm4
            movq mm6, mm5
            psubusw mm4, mm6
            psubusw mm5, mm3
            por mm4, mm5
            psubw mm4, qword ptr limit
            psraw mm4, 0xf
            movq mm2, mm4
            pand mm4, mm6
            pandn mm2, mm3
            por mm2, mm4
            movq mm3, mm1
            paddw mm3, mm3
            paddw mm3, mm1
            movq mm4, qword ptr [edi + 0x10]
            paddw mm3, qword ptr [edi + 0x20]
            paddw mm4, qword ptr [edi + 0x30]
            paddw mm3, qword ptr [edi + 0x40]
            paddw mm4, qword ptr packedFour
            paddw mm3, mm4
            movq mm4, mm3
            movq mm5, qword ptr [edi + 0x10]
            paddw mm4, mm5
            psllw mm4, 1
            psubw mm4, qword ptr [edi + 0x40]
            paddw mm4, qword ptr [edi + 0x50]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm7
            paddw mm4, mm5
            movq qword ptr [esi], mm4
            movq mm5, qword ptr [edi + 0x20]
            psubw mm3, mm1
            paddw mm3, qword ptr [edi + 0x50]
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            psubw mm4, qword ptr [edi + 0x50]
            paddw mm4, qword ptr [edi + 0x60]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm7
            paddw mm4, mm5
            movq qword ptr [esi + 0x10], mm4
            movq mm5, qword ptr [edi + 0x30]
            psubw mm3, mm1
            paddw mm3, qword ptr [edi + 0x60]
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            psubw mm4, qword ptr [edi + 0x60]
            paddw mm4, qword ptr [edi + 0x70]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm7
            paddw mm4, mm5
            movq qword ptr [esi + 0x20], mm4
            movq mm5, qword ptr [edi + 0x40]
            psubw mm3, mm1
            paddw mm3, qword ptr [edi + 0x70]
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            paddw mm4, mm1
            psubw mm4, qword ptr [edi + 0x10]
            psubw mm4, qword ptr [edi + 0x70]
            paddw mm4, qword ptr [edi + 0x80]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm7
            paddw mm4, mm5
            movq qword ptr [esi + 0x30], mm4
            movq mm5, qword ptr [edi + 0x50]
            psubw mm3, qword ptr [edi + 0x10]
            paddw mm3, qword ptr [edi + 0x80]
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            paddw mm4, qword ptr [edi + 0x10]
            psubw mm4, qword ptr [edi + 0x20]
            psubw mm4, qword ptr [edi + 0x80]
            paddw mm4, mm2
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm7
            paddw mm4, mm5
            movq qword ptr [esi + 0x40], mm4
            movq mm5, qword ptr [edi + 0x60]
            psubw mm3, qword ptr [edi + 0x20]
            paddw mm3, mm2
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            paddw mm4, qword ptr [edi + 0x20]
            psubw mm4, qword ptr [edi + 0x30]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm7
            paddw mm4, mm5
            movq qword ptr [esi + 0x50], mm4
            movq mm5, qword ptr [edi + 0x70]
            psubw mm3, qword ptr [edi + 0x30]
            paddw mm3, mm2
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            paddw mm4, qword ptr [edi + 0x30]
            psubw mm4, qword ptr [edi + 0x40]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm7
            paddw mm4, mm5
            movq qword ptr [esi + 0x60], mm4
            movq mm5, qword ptr [edi + 0x80]
            psubw mm3, qword ptr [edi + 0x40]
            paddw mm3, mm2
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            paddw mm4, qword ptr [edi + 0x40]
            psubw mm4, qword ptr [edi + 0x50]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm7
            paddw mm4, mm5
            movq qword ptr [esi + 0x70], mm4
            add edi, 8
            add esi, 8
            movq mm5, qword ptr [edi]
            movq mm4, qword ptr [edi + 0x10]
            movq mm3, mm4
            movq mm6, mm5
            psubusw mm4, mm6
            psubusw mm5, mm3
            por mm4, mm5
            psubw mm4, qword ptr limit
            psraw mm4, 0xf
            movq mm1, mm4
            pand mm4, mm6
            pandn mm1, mm3
            por mm1, mm4
            movq mm4, qword ptr [edi + 0x80]
            movq mm5, qword ptr [edi + 0x90]
            movq mm3, mm4
            movq mm6, mm5
            psubusw mm4, mm6
            psubusw mm5, mm3
            por mm4, mm5
            psubw mm4, qword ptr limit
            psraw mm4, 0xf
            movq mm2, mm4
            pand mm4, mm6
            pandn mm2, mm3
            por mm2, mm4
            movq mm3, mm1
            paddw mm3, mm3
            paddw mm3, mm1
            movq mm4, qword ptr [edi + 0x10]
            paddw mm3, qword ptr [edi + 0x20]
            paddw mm4, qword ptr [edi + 0x30]
            paddw mm3, qword ptr [edi + 0x40]
            paddw mm4, qword ptr packedFour
            paddw mm3, mm4
            movq mm4, mm3
            movq mm5, qword ptr [edi + 0x10]
            paddw mm4, mm5
            psllw mm4, 1
            psubw mm4, qword ptr [edi + 0x40]
            paddw mm4, qword ptr [edi + 0x50]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm0
            paddw mm4, mm5
            movq qword ptr [esi], mm4
            movq mm5, qword ptr [edi + 0x20]
            psubw mm3, mm1
            paddw mm3, qword ptr [edi + 0x50]
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            psubw mm4, qword ptr [edi + 0x50]
            paddw mm4, qword ptr [edi + 0x60]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm0
            paddw mm4, mm5
            movq qword ptr [esi + 0x10], mm4
            movq mm5, qword ptr [edi + 0x30]
            psubw mm3, mm1
            paddw mm3, qword ptr [edi + 0x60]
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            psubw mm4, qword ptr [edi + 0x60]
            paddw mm4, qword ptr [edi + 0x70]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm0
            paddw mm4, mm5
            movq qword ptr [esi + 0x20], mm4
            movq mm5, qword ptr [edi + 0x40]
            psubw mm3, mm1
            paddw mm3, qword ptr [edi + 0x70]
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            paddw mm4, mm1
            psubw mm4, qword ptr [edi + 0x10]
            psubw mm4, qword ptr [edi + 0x70]
            paddw mm4, qword ptr [edi + 0x80]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm0
            paddw mm4, mm5
            movq qword ptr [esi + 0x30], mm4
            movq mm5, qword ptr [edi + 0x50]
            psubw mm3, qword ptr [edi + 0x10]
            paddw mm3, qword ptr [edi + 0x80]
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            paddw mm4, qword ptr [edi + 0x10]
            psubw mm4, qword ptr [edi + 0x20]
            psubw mm4, qword ptr [edi + 0x80]
            paddw mm4, mm2
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm0
            paddw mm4, mm5
            movq qword ptr [esi + 0x40], mm4
            movq mm5, qword ptr [edi + 0x60]
            psubw mm3, qword ptr [edi + 0x20]
            paddw mm3, mm2
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            paddw mm4, qword ptr [edi + 0x20]
            psubw mm4, qword ptr [edi + 0x30]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm0
            paddw mm4, mm5
            movq qword ptr [esi + 0x50], mm4
            movq mm5, qword ptr [edi + 0x70]
            psubw mm3, qword ptr [edi + 0x30]
            paddw mm3, mm2
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            paddw mm4, qword ptr [edi + 0x30]
            psubw mm4, qword ptr [edi + 0x40]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm0
            paddw mm4, mm5
            movq qword ptr [esi + 0x60], mm4
            movq mm5, qword ptr [edi + 0x80]
            psubw mm3, qword ptr [edi + 0x40]
            paddw mm3, mm2
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            paddw mm4, qword ptr [edi + 0x40]
            psubw mm4, qword ptr [edi + 0x50]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm0
            paddw mm4, mm5
            movq qword ptr [esi + 0x70], mm4
            add edi, 8
            sub esi, 8
            mov ebp, dword ptr destinationWalk
            lea ebp, [ebp + edx*4]
            movq mm0, qword ptr [esi]
            packuswb mm0, qword ptr [esi + 8]
            movq qword ptr [ebp], mm0
            movq mm1, qword ptr [esi + 0x10]
            packuswb mm1, qword ptr [esi + 0x18]
            movq qword ptr [ebp + ecx], mm1
            movq mm2, qword ptr [esi + 0x20]
            packuswb mm2, qword ptr [esi + 0x28]
            movq qword ptr [ebp + ecx*2], mm2
            movq mm3, qword ptr [esi + 0x30]
            packuswb mm3, qword ptr [esi + 0x38]
            lea ebp, [ebp + ecx*4]
            movq qword ptr [ebp + edx], mm3
            movq mm0, qword ptr [esi + 0x40]
            packuswb mm0, qword ptr [esi + 0x48]
            movq qword ptr [ebp], mm0
            movq mm1, qword ptr [esi + 0x50]
            packuswb mm1, qword ptr [esi + 0x58]
            movq qword ptr [ebp + ecx], mm1
            movq mm2, qword ptr [esi + 0x60]
            packuswb mm2, qword ptr [esi + 0x68]
            movq qword ptr [ebp + ecx*2], mm2
            movq mm3, qword ptr [esi + 0x70]
            packuswb mm3, qword ptr [esi + 0x78]
            lea ebp, [ebp + ecx*2]
            movq qword ptr [ebp + ecx], mm3
            pop edi
            pop esi
            pop edx
            pop ecx
            pop ebp
            pop eax
            }
            context->m_28[index] += (unsigned int)leftLow[0] + leftLow[1] + leftLow[2] + leftLow[3]
                + leftHigh[0] + leftHigh[1] + leftHigh[2] + leftHigh[3];
            context->m_28[tableIndex] += (unsigned int)rightLow[0] + rightLow[1] + rightLow[2] + rightLow[3]
                + rightHigh[0] + rightHigh[1] + rightHigh[2] + rightHigh[3];
        }
        else
        {
            __asm
            {
            push esi
            push edi
            push ecx
            mov esi, sourceWalk
            mov edi, destinationWalk
            push edx
            mov ecx, dword ptr stride
            xor edx, edx
            sub edx, ecx
            lea esi, [esi + edx*4]
            movq mm0, qword ptr [esi]
            movq qword ptr [edi + edx*4], mm0
            lea edi, [edi + edx*4]
            movq mm1, qword ptr [esi + ecx]
            movq qword ptr [edi + ecx], mm1
            movq mm2, qword ptr [esi + ecx*2]
            lea esi, [esi + ecx*4]
            movq qword ptr [edi + ecx*2], mm2
            lea edi, [edi + ecx*4]
            movq mm3, qword ptr [esi + edx]
            movq qword ptr [edi + edx], mm3
            movq mm4, qword ptr [esi]
            movq mm5, qword ptr [esi + ecx]
            movq qword ptr [edi], mm4
            movq mm6, qword ptr [esi + ecx*2]
            lea esi, [esi + ecx*4]
            movq qword ptr [edi + ecx], mm5
            movq qword ptr [edi + ecx*2], mm6
            movq mm7, qword ptr [esi + edx]
            lea edi, [edi + ecx*4]
            movq qword ptr [edi + edx], mm7
            pop edx
            pop ecx
            pop edi
            pop esi
            }
        }
        sourceWalk += 8;
        destinationWalk += 8;
    }

    destinationWalk += 8 - ((unsigned int)stride << 3) - (count << 3);
    sourceWalk = destinationWalk;
    index = start;
    end = count + index - 1;
    for (; index < end;)
    {
        unsigned int value = strength[context->m_24[index + 1]];
        if (value > 3)
        {
            limit[0] = (unsigned short)value;
            limit[1] = (unsigned short)value;
            limit[2] = (unsigned short)value;
            limit[3] = (unsigned short)value;
            _ReadWriteBarrier();
            samples[0] = sourceWalk[0 * stride - 5];
            samples[72] = sourceWalk[0 * stride + 4];
            samples[1] = sourceWalk[1 * stride - 5];
            samples[73] = sourceWalk[1 * stride + 4];
            samples[2] = sourceWalk[2 * stride - 5];
            samples[74] = sourceWalk[2 * stride + 4];
            samples[3] = sourceWalk[3 * stride - 5];
            samples[75] = sourceWalk[3 * stride + 4];
            samples[4] = sourceWalk[4 * stride - 5];
            samples[76] = sourceWalk[4 * stride + 4];
            samples[5] = sourceWalk[5 * stride - 5];
            samples[77] = sourceWalk[5 * stride + 4];
            samples[6] = sourceWalk[6 * stride - 5];
            samples[78] = sourceWalk[6 * stride + 4];
            samples[7] = sourceWalk[7 * stride - 5];
            samples[79] = sourceWalk[7 * stride + 4];
            __asm
            {
            push eax
            push ebp
            push ecx
            push edx
            push esi
            push edi
            movq mm0, qword ptr limit
            movq mm1, qword ptr packedThree
            pmullw mm1, mm0
            pmullw mm1, mm0
            psrlw mm1, 5
            movq qword ptr varianceLimit, mm1
            mov eax, dword ptr sourceWalk
            xor edx, edx
            sub eax, 4
            lea esi, filtered
            lea edi, samples
            mov ecx, dword ptr stride
            sub edx, ecx
            movq mm0, qword ptr [eax]
            movq mm1, qword ptr [eax + ecx]
            movq mm2, qword ptr [eax + ecx*2]
            lea eax, [eax + ecx*4]
            movq mm3, qword ptr [eax + edx]
            movq mm4, mm0
            punpcklbw mm0, mm1
            punpckhbw mm4, mm1
            movq mm5, mm2
            punpcklbw mm2, mm3
            punpckhbw mm5, mm3
            movq mm1, mm0
            punpcklwd mm0, mm2
            punpckhwd mm1, mm2
            movq mm2, mm4
            punpckhwd mm4, mm5
            punpcklwd mm2, mm5
            pxor mm7, mm7
            movq mm5, mm0
            punpcklbw mm0, mm7
            movq qword ptr [edi + 0x10], mm0
            punpckhbw mm5, mm7
            movq mm0, mm1
            movq qword ptr [edi + 0x20], mm5
            punpcklbw mm1, mm7
            punpckhbw mm0, mm7
            movq qword ptr [edi + 0x30], mm1
            movq mm3, mm2
            movq mm5, mm4
            movq qword ptr [edi + 0x40], mm0
            punpcklbw mm2, mm7
            punpckhbw mm3, mm7
            movq qword ptr [edi + 0x50], mm2
            punpcklbw mm4, mm7
            punpckhbw mm5, mm7
            movq qword ptr [edi + 0x60], mm3
            movq mm0, qword ptr [eax]
            movq mm1, qword ptr [eax + ecx]
            movq qword ptr [edi + 0x70], mm4
            movq mm2, qword ptr [eax + ecx*2]
            lea eax, [eax + ecx*4]
            movq qword ptr [edi + 0x80], mm5
            movq mm4, mm0
            movq mm3, qword ptr [eax + edx]
            punpcklbw mm0, mm1
            punpckhbw mm4, mm1
            movq mm5, mm2
            punpcklbw mm2, mm3
            punpckhbw mm5, mm3
            movq mm1, mm0
            punpcklwd mm0, mm2
            punpckhwd mm1, mm2
            movq mm2, mm4
            punpckhwd mm4, mm5
            punpcklwd mm2, mm5
            movq mm5, mm0
            punpcklbw mm0, mm7
            movq qword ptr [edi + 0x18], mm0
            punpckhbw mm5, mm7
            movq mm0, mm1
            movq qword ptr [edi + 0x28], mm5
            punpcklbw mm1, mm7
            punpckhbw mm0, mm7
            movq qword ptr [edi + 0x38], mm1
            movq mm3, mm2
            movq mm5, mm4
            movq qword ptr [edi + 0x48], mm0
            punpcklbw mm2, mm7
            punpckhbw mm3, mm7
            movq qword ptr [edi + 0x58], mm2
            punpcklbw mm4, mm7
            punpckhbw mm5, mm7
            movq qword ptr [edi + 0x68], mm3
            movq qword ptr [edi + 0x78], mm4
            movq qword ptr [edi + 0x88], mm5
            pcmpeqw mm3, mm3
            psllw mm3, 0xf
            psrlw mm3, 8
            movq mm2, qword ptr [edi + 0x10]
            movq mm6, qword ptr [edi + 0x50]
            psubw mm2, mm3
            psubw mm6, mm3
            movq mm0, mm2
            movq mm4, mm6
            pmullw mm2, mm2
            pmullw mm6, mm6
            movq mm1, mm2
            movq mm5, mm6
            movq mm2, qword ptr [edi + 0x20]
            movq mm6, qword ptr [edi + 0x60]
            psubw mm2, mm3
            psubw mm6, mm3
            paddw mm0, mm2
            paddw mm4, mm6
            pmullw mm2, mm2
            pmullw mm6, mm6
            paddw mm1, mm2
            paddw mm5, mm6
            movq mm2, qword ptr [edi + 0x30]
            movq mm6, qword ptr [edi + 0x70]
            psubw mm2, mm3
            psubw mm6, mm3
            paddw mm0, mm2
            paddw mm4, mm6
            pmullw mm2, mm2
            pmullw mm6, mm6
            paddw mm1, mm2
            paddw mm5, mm6
            movq mm2, qword ptr [edi + 0x40]
            movq mm6, qword ptr [edi + 0x80]
            psubw mm2, mm3
            psubw mm6, mm3
            paddw mm0, mm2
            paddw mm4, mm6
            pmullw mm2, mm2
            pmullw mm6, mm6
            paddw mm1, mm2
            paddw mm5, mm6
            movq mm7, mm3
            psrlw mm7, 7
            movq mm2, mm0
            movq mm6, mm4
            paddw mm0, mm7
            paddw mm4, mm7
            psraw mm2, 1
            psraw mm6, 1
            psraw mm0, 1
            psraw mm4, 1
            pmullw mm2, mm0
            pmullw mm6, mm4
            psubw mm1, mm2
            psubw mm5, mm6
            movq qword ptr leftLow, mm1
            movq qword ptr rightLow, mm5
            movq mm7, qword ptr varianceLimit
            movq mm2, mm1
            movq mm6, mm5
            psubw mm1, mm7
            psubw mm5, mm7
            psraw mm1, 0xf
            psraw mm5, 0xf
            psraw mm2, 0xf
            psraw mm6, 0xf
            movq mm7, qword ptr [edi + 0x40]
            pandn mm2, mm1
            pandn mm6, mm5
            movq mm4, qword ptr [edi + 0x50]
            pand mm6, mm2
            movq mm2, mm7
            psubusw mm7, mm4
            psubusw mm4, mm2
            por mm7, mm4
            psubw mm7, qword ptr limit
            psraw mm7, 0xf
            pand mm7, mm6
            add edi, 8
            movq mm2, qword ptr [edi + 0x10]
            movq mm6, qword ptr [edi + 0x50]
            psubw mm2, mm3
            psubw mm6, mm3
            movq mm0, mm2
            movq mm4, mm6
            pmullw mm2, mm2
            pmullw mm6, mm6
            movq mm1, mm2
            movq mm5, mm6
            movq mm2, qword ptr [edi + 0x20]
            movq mm6, qword ptr [edi + 0x60]
            psubw mm2, mm3
            psubw mm6, mm3
            paddw mm0, mm2
            paddw mm4, mm6
            pmullw mm2, mm2
            pmullw mm6, mm6
            paddw mm1, mm2
            paddw mm5, mm6
            movq mm2, qword ptr [edi + 0x30]
            movq mm6, qword ptr [edi + 0x70]
            psubw mm2, mm3
            psubw mm6, mm3
            paddw mm0, mm2
            paddw mm4, mm6
            pmullw mm2, mm2
            pmullw mm6, mm6
            paddw mm1, mm2
            paddw mm5, mm6
            movq mm2, qword ptr [edi + 0x40]
            movq mm6, qword ptr [edi + 0x80]
            psubw mm2, mm3
            psubw mm6, mm3
            paddw mm0, mm2
            paddw mm4, mm6
            pmullw mm2, mm2
            pmullw mm6, mm6
            paddw mm1, mm2
            paddw mm5, mm6
            psrlw mm3, 7
            movq mm2, mm0
            movq mm6, mm4
            paddw mm0, mm3
            paddw mm4, mm3
            psraw mm2, 1
            psraw mm6, 1
            psraw mm0, 1
            psraw mm4, 1
            pmullw mm2, mm0
            pmullw mm6, mm4
            psubw mm1, mm2
            psubw mm5, mm6
            movq qword ptr leftHigh, mm1
            movq qword ptr rightHigh, mm5
            movq mm3, qword ptr varianceLimit
            movq mm2, mm1
            movq mm6, mm5
            psubw mm1, mm3
            psubw mm5, mm3
            psraw mm6, 0xf
            psraw mm2, 0xf
            psraw mm1, 0xf
            psraw mm5, 0xf
            movq mm0, qword ptr [edi + 0x40]
            pandn mm2, mm1
            pandn mm6, mm5
            movq mm4, qword ptr [edi + 0x50]
            pand mm6, mm2
            movq mm2, mm0
            psubusw mm0, mm4
            psubusw mm4, mm2
            por mm0, mm4
            psubw mm0, qword ptr limit
            psraw mm0, 0xf
            pand mm0, mm6
            sub edi, 8
            movq mm5, qword ptr [edi]
            movq mm4, qword ptr [edi + 0x10]
            movq mm3, mm4
            movq mm6, mm5
            psubusw mm4, mm6
            psubusw mm5, mm3
            por mm4, mm5
            psubw mm4, qword ptr limit
            psraw mm4, 0xf
            movq mm1, mm4
            pand mm4, mm6
            pandn mm1, mm3
            por mm1, mm4
            movq mm4, qword ptr [edi + 0x80]
            movq mm5, qword ptr [edi + 0x90]
            movq mm3, mm4
            movq mm6, mm5
            psubusw mm4, mm6
            psubusw mm5, mm3
            por mm4, mm5
            psubw mm4, qword ptr limit
            psraw mm4, 0xf
            movq mm2, mm4
            pand mm4, mm6
            pandn mm2, mm3
            por mm2, mm4
            movq mm3, mm1
            paddw mm3, mm3
            paddw mm3, mm1
            movq mm4, qword ptr [edi + 0x10]
            paddw mm3, qword ptr [edi + 0x20]
            paddw mm4, qword ptr [edi + 0x30]
            paddw mm3, qword ptr [edi + 0x40]
            paddw mm4, qword ptr packedFour
            paddw mm3, mm4
            movq mm4, mm3
            movq mm5, qword ptr [edi + 0x10]
            paddw mm4, mm5
            psllw mm4, 1
            psubw mm4, qword ptr [edi + 0x40]
            paddw mm4, qword ptr [edi + 0x50]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm7
            paddw mm4, mm5
            movq qword ptr [esi], mm4
            movq mm5, qword ptr [edi + 0x20]
            psubw mm3, mm1
            paddw mm3, qword ptr [edi + 0x50]
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            psubw mm4, qword ptr [edi + 0x50]
            paddw mm4, qword ptr [edi + 0x60]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm7
            paddw mm4, mm5
            movq qword ptr [esi + 0x10], mm4
            movq mm5, qword ptr [edi + 0x30]
            psubw mm3, mm1
            paddw mm3, qword ptr [edi + 0x60]
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            psubw mm4, qword ptr [edi + 0x60]
            paddw mm4, qword ptr [edi + 0x70]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm7
            paddw mm4, mm5
            movq qword ptr [esi + 0x20], mm4
            movq mm5, qword ptr [edi + 0x40]
            psubw mm3, mm1
            paddw mm3, qword ptr [edi + 0x70]
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            paddw mm4, mm1
            psubw mm4, qword ptr [edi + 0x10]
            psubw mm4, qword ptr [edi + 0x70]
            paddw mm4, qword ptr [edi + 0x80]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm7
            paddw mm4, mm5
            movq qword ptr [esi + 0x30], mm4
            movq mm5, qword ptr [edi + 0x50]
            psubw mm3, qword ptr [edi + 0x10]
            paddw mm3, qword ptr [edi + 0x80]
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            paddw mm4, qword ptr [edi + 0x10]
            psubw mm4, qword ptr [edi + 0x20]
            psubw mm4, qword ptr [edi + 0x80]
            paddw mm4, mm2
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm7
            paddw mm4, mm5
            movq qword ptr [esi + 0x40], mm4
            movq mm5, qword ptr [edi + 0x60]
            psubw mm3, qword ptr [edi + 0x20]
            paddw mm3, mm2
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            paddw mm4, qword ptr [edi + 0x20]
            psubw mm4, qword ptr [edi + 0x30]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm7
            paddw mm4, mm5
            movq qword ptr [esi + 0x50], mm4
            movq mm5, qword ptr [edi + 0x70]
            psubw mm3, qword ptr [edi + 0x30]
            paddw mm3, mm2
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            paddw mm4, qword ptr [edi + 0x30]
            psubw mm4, qword ptr [edi + 0x40]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm7
            paddw mm4, mm5
            movq qword ptr [esi + 0x60], mm4
            movq mm5, qword ptr [edi + 0x80]
            psubw mm3, qword ptr [edi + 0x40]
            paddw mm3, mm2
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            paddw mm4, qword ptr [edi + 0x40]
            psubw mm4, qword ptr [edi + 0x50]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm7
            paddw mm4, mm5
            movq qword ptr [esi + 0x70], mm4
            add edi, 8
            add esi, 8
            movq mm5, qword ptr [edi]
            movq mm4, qword ptr [edi + 0x10]
            movq mm3, mm4
            movq mm6, mm5
            psubusw mm4, mm6
            psubusw mm5, mm3
            por mm4, mm5
            psubw mm4, qword ptr limit
            psraw mm4, 0xf
            movq mm1, mm4
            pand mm4, mm6
            pandn mm1, mm3
            por mm1, mm4
            movq mm4, qword ptr [edi + 0x80]
            movq mm5, qword ptr [edi + 0x90]
            movq mm3, mm4
            movq mm6, mm5
            psubusw mm4, mm6
            psubusw mm5, mm3
            por mm4, mm5
            psubw mm4, qword ptr limit
            psraw mm4, 0xf
            movq mm2, mm4
            pand mm4, mm6
            pandn mm2, mm3
            por mm2, mm4
            movq mm3, mm1
            paddw mm3, mm3
            paddw mm3, mm1
            movq mm4, qword ptr [edi + 0x10]
            paddw mm3, qword ptr [edi + 0x20]
            paddw mm4, qword ptr [edi + 0x30]
            paddw mm3, qword ptr [edi + 0x40]
            paddw mm4, qword ptr packedFour
            paddw mm3, mm4
            movq mm4, mm3
            movq mm5, qword ptr [edi + 0x10]
            paddw mm4, mm5
            psllw mm4, 1
            psubw mm4, qword ptr [edi + 0x40]
            paddw mm4, qword ptr [edi + 0x50]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm0
            paddw mm4, mm5
            movq qword ptr [esi], mm4
            movq mm5, qword ptr [edi + 0x20]
            psubw mm3, mm1
            paddw mm3, qword ptr [edi + 0x50]
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            psubw mm4, qword ptr [edi + 0x50]
            paddw mm4, qword ptr [edi + 0x60]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm0
            paddw mm4, mm5
            movq qword ptr [esi + 0x10], mm4
            movq mm5, qword ptr [edi + 0x30]
            psubw mm3, mm1
            paddw mm3, qword ptr [edi + 0x60]
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            psubw mm4, qword ptr [edi + 0x60]
            paddw mm4, qword ptr [edi + 0x70]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm0
            paddw mm4, mm5
            movq qword ptr [esi + 0x20], mm4
            movq mm5, qword ptr [edi + 0x40]
            psubw mm3, mm1
            paddw mm3, qword ptr [edi + 0x70]
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            paddw mm4, mm1
            psubw mm4, qword ptr [edi + 0x10]
            psubw mm4, qword ptr [edi + 0x70]
            paddw mm4, qword ptr [edi + 0x80]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm0
            paddw mm4, mm5
            movq qword ptr [esi + 0x30], mm4
            movq mm5, qword ptr [edi + 0x50]
            psubw mm3, qword ptr [edi + 0x10]
            paddw mm3, qword ptr [edi + 0x80]
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            paddw mm4, qword ptr [edi + 0x10]
            psubw mm4, qword ptr [edi + 0x20]
            psubw mm4, qword ptr [edi + 0x80]
            paddw mm4, mm2
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm0
            paddw mm4, mm5
            movq qword ptr [esi + 0x40], mm4
            movq mm5, qword ptr [edi + 0x60]
            psubw mm3, qword ptr [edi + 0x20]
            paddw mm3, mm2
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            paddw mm4, qword ptr [edi + 0x20]
            psubw mm4, qword ptr [edi + 0x30]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm0
            paddw mm4, mm5
            movq qword ptr [esi + 0x50], mm4
            movq mm5, qword ptr [edi + 0x70]
            psubw mm3, qword ptr [edi + 0x30]
            paddw mm3, mm2
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            paddw mm4, qword ptr [edi + 0x30]
            psubw mm4, qword ptr [edi + 0x40]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm0
            paddw mm4, mm5
            movq qword ptr [esi + 0x60], mm4
            movq mm5, qword ptr [edi + 0x80]
            psubw mm3, qword ptr [edi + 0x40]
            paddw mm3, mm2
            movq mm4, mm5
            paddw mm4, mm3
            paddw mm4, mm4
            paddw mm4, qword ptr [edi + 0x40]
            psubw mm4, qword ptr [edi + 0x50]
            psraw mm4, 4
            psubw mm4, mm5
            pand mm4, mm0
            paddw mm4, mm5
            movq qword ptr [esi + 0x70], mm4
            mov eax, dword ptr destinationWalk
            add edi, 8
            sub esi, 8
            sub eax, 4
            movq mm0, qword ptr [esi]
            movq mm1, qword ptr [esi + 0x10]
            movq mm4, mm0
            punpcklwd mm0, mm1
            punpckhwd mm4, mm1
            movq mm2, qword ptr [esi + 0x20]
            movq mm3, qword ptr [esi + 0x30]
            movq mm5, mm2
            punpcklwd mm2, mm3
            punpckhwd mm5, mm3
            movq mm1, mm0
            punpckldq mm0, mm2
            movq qword ptr [edi], mm0
            punpckhdq mm1, mm2
            movq mm0, mm4
            movq qword ptr [edi + 0x10], mm1
            punpckldq mm0, mm5
            punpckhdq mm4, mm5
            movq mm1, qword ptr [esi + 0x40]
            movq mm2, qword ptr [esi + 0x50]
            movq mm5, qword ptr [esi + 0x60]
            movq mm6, qword ptr [esi + 0x70]
            movq mm3, mm1
            movq mm7, mm5
            punpcklwd mm1, mm2
            punpckhwd mm3, mm2
            punpcklwd mm5, mm6
            punpckhwd mm7, mm6
            movq mm2, mm1
            movq mm6, mm3
            punpckldq mm1, mm5
            punpckhdq mm2, mm5
            punpckldq mm3, mm7
            punpckhdq mm6, mm7
            movq mm5, qword ptr [edi]
            packuswb mm5, mm1
            movq qword ptr [eax], mm5
            movq mm7, qword ptr [edi + 0x10]
            packuswb mm7, mm2
            movq qword ptr [eax + ecx], mm7
            packuswb mm0, mm3
            packuswb mm4, mm6
            movq qword ptr [eax + ecx*2], mm0
            lea eax, [eax + ecx*4]
            movq qword ptr [eax + edx], mm4
            add edi, 8
            add esi, 8
            movq mm0, qword ptr [esi]
            movq mm1, qword ptr [esi + 0x10]
            movq mm4, mm0
            punpcklwd mm0, mm1
            punpckhwd mm4, mm1
            movq mm2, qword ptr [esi + 0x20]
            movq mm3, qword ptr [esi + 0x30]
            movq mm5, mm2
            punpcklwd mm2, mm3
            punpckhwd mm5, mm3
            movq mm1, mm0
            punpckldq mm0, mm2
            movq qword ptr [edi], mm0
            punpckhdq mm1, mm2
            movq mm0, mm4
            movq qword ptr [edi + 0x10], mm1
            punpckldq mm0, mm5
            punpckhdq mm4, mm5
            movq mm1, qword ptr [esi + 0x40]
            movq mm2, qword ptr [esi + 0x50]
            movq mm5, qword ptr [esi + 0x60]
            movq mm6, qword ptr [esi + 0x70]
            movq mm3, mm1
            movq mm7, mm5
            punpcklwd mm1, mm2
            punpckhwd mm3, mm2
            punpcklwd mm5, mm6
            punpckhwd mm7, mm6
            movq mm2, mm1
            movq mm6, mm3
            punpckldq mm1, mm5
            punpckhdq mm2, mm5
            punpckldq mm3, mm7
            punpckhdq mm6, mm7
            movq mm5, qword ptr [edi]
            packuswb mm5, mm1
            movq qword ptr [eax], mm5
            movq mm7, qword ptr [edi + 0x10]
            packuswb mm7, mm2
            movq qword ptr [eax + ecx], mm7
            packuswb mm0, mm3
            packuswb mm4, mm6
            movq qword ptr [eax + ecx*2], mm0
            lea eax, [eax + ecx*4]
            movq qword ptr [eax + edx], mm4
            pop edi
            pop esi
            pop edx
            pop ecx
            pop ebp
            pop eax
            }
            context->m_28[index] += (unsigned int)leftLow[0] + leftLow[1] + leftLow[2] + leftLow[3]
                + leftHigh[0] + leftHigh[1] + leftHigh[2] + leftHigh[3];
            context->m_28[index + 1] += (unsigned int)rightLow[0] + rightLow[1] + rightLow[2] + rightLow[3]
                + rightHigh[0] + rightHigh[1] + rightHigh[2] + rightHigh[3];
        }
        ++index;
        sourceWalk += 8;
        destinationWalk += 8;
    }
}
