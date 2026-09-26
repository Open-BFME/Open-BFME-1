// ?rva00849E20DecodeFlags@@YAII@Z
// partial score=0.5902 date=2026-09-26
// ?rva00849E20DecodeFlags@@YAII@Z
// 0x00849E20: low two bits select 8/16/24 or pass through the input;
// every case then promotes bit 3 to bit 0 and bit 15 to bit 2.
// A volatile read keeps the retail stack reload in the pass-through case.
unsigned int __cdecl rva00849E20DecodeFlags(unsigned int p)
{
    unsigned int result;
    switch (p & 3)
    {
    case 0:
        result = 8;
        break;
    case 1:
        result = 0x10;
        break;
    case 2:
        result = 0x18;
        break;
    default:
        result = *(volatile unsigned int *)&p;
        break;
    }

    if (p & 8)
        result |= 1;
    if (p & 0x8000)
        result |= 4;
    return result;
}
