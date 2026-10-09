// ?Rva009B3F40Vp6Reconstruct@@YAXPAXPAF1E@Z
// partial score=0.9532 date=2026-10-09
// cl: /O2 /Z7
#include <stdlib.h>
extern unsigned char g_Rva01142608[];
extern "C" int g_Va012D8258[];

struct Rva009A6780State {
    int index, at0004;
    short at0008[8], at0018[8], at0028[8];
    unsigned char pad0038[0x158];
    int at0190[2][64], at0390[2][64], at0590[2][64], at0790[2][64];
};

void Rva009B3F40Vp6Reconstruct(void *context, short *source, short *destination, unsigned char selector)
{
    __declspec(align(16)) short frame[64];
    Rva009A6780State *state = static_cast<Rva009A6780State *>(context);
    unsigned char *bank = reinterpret_cast<unsigned char *>(state) + (g_Rva01142608[selector] << 8);
    int multiplier = *reinterpret_cast<int *>(bank + 0x190);
    short *offsetPointer = state->at0008;
    short *reciprocal = state->at0018;
    int run = 0;
    __asm {
        mov esi, source
        xor ecx, ecx
        mov edi, offsetPointer
        movdqu xmm2, xmmword ptr [edi]
        mov edi, reciprocal
        movdqu xmm3, xmmword ptr [edi]
        lea edi, frame
        mov eax, destination
        pxor xmm7, xmm7
    simdLoop:
        movdqa xmm0, xmmword ptr [esi + ecx]
        movdqa xmm1, xmm0
        psraw xmm1, 15
        pxor xmm0, xmm1
        psubw xmm0, xmm1
        paddw xmm0, xmm2
        pmulhuw xmm0, xmm3
        pxor xmm0, xmm1
        psubw xmm0, xmm1
        movdqa xmmword ptr [edi + ecx], xmm0
        movdqa xmmword ptr [eax + ecx], xmm7
        add ecx, 16
        cmp ecx, 128
        jl simdLoop
    }
    int value = source[0];
    int threshold = *reinterpret_cast<int *>(bank + 0x590);
    if (value >= threshold)
        destination[0] = static_cast<short>(((value + *reinterpret_cast<int *>(bank + 0x390)) * multiplier) >> 16);
    else if (value <= -threshold)
        destination[0] = static_cast<short>(((value - *reinterpret_cast<int *>(bank + 0x390)) * multiplier + 65535) >> 16);
    else
        run = 1;
    for (unsigned int i = 1; i < 64; ++i) {
        int position = g_Va012D8258[i];
        unsigned int quantized = static_cast<unsigned short>(frame[position]);
        if (quantized == 0)
            ++run;
        else {
            int magnitude = abs(source[position]);
            int thresholdRun = reinterpret_cast<int *>(bank + 0x790)[run];
            thresholdRun += reinterpret_cast<int *>(bank + 0x590)[position];
            if (magnitude < thresholdRun)
                ++run;
            else {
                run = 0;
                destination[i] = static_cast<short>(quantized);
            }
        }
    }
}
