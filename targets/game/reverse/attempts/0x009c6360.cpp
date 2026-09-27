// ?Rva009C6360@@YAXPBF0PAI@Z
// partial score=0.74 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc
void __cdecl Rva009C6360(const short *first, const short *second, unsigned int *output)
{
    const volatile short *secondPointer = second;
    const volatile short *firstPointer = first;
    int secondValue = *secondPointer;
    int firstValue = *firstPointer;
    int value = (firstValue * secondValue + 15) >> 5;
    unsigned int low = (unsigned short)value;
    unsigned int fill = (low << 16) | low;
    __asm
    {
        mov edi, output
        mov ecx, 32
        mov eax, fill
        rep stosd
    }
}
