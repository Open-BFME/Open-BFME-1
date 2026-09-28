// Address-derived cdecl configuration ABI proven by VP6 stream invoke callers.
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
class Rva009A5EB0Owner;
struct Rva009A9070Context;
struct Rva009A9070Source;
void Rva009A5EB0(Rva009A5EB0Owner *, int);
void Rva009A9070CopyStreams(Rva009A9070Context *, Rva009A9070Source *, int);
void Rva009A4E50Configure(void *context, unsigned selector, int value)
{
    if (selector > 9) return;
again:
    switch (selector) {
    case 1: {
        unsigned area = *(unsigned *)((char *)context + 0x1b4) * *(unsigned *)((char *)context + 0x1b0);
        double ratio = sqrt((double)area) / (double)((*(unsigned *)((char *)context + 0x1a4) * value) / 100u) * 100.0;
        *(int *)((char *)context + 0x1a8) = value;
        if (ratio > 150.0) *(int *)((char *)context + 0x1a0) = 0;
        else if (ratio > 100.0) *(int *)((char *)context + 0x1a0) = 8;
        else if (ratio > 90.0) *(int *)((char *)context + 0x1a0) = 4;
        else if (ratio > 80.0) *(int *)((char *)context + 0x1a0) = 5;
        else *(int *)((char *)context + 0x1a0) = 6;
        return;
    }
    case 9:
        *(int *)((char *)context + 0x4948) = value;
        Rva009A5EB0(*(Rva009A5EB0Owner **)((char *)context + 0x298), value);
        return;
    case 7:
        Rva009A9070CopyStreams(*(Rva009A9070Context **)((char *)context + 0x298), (Rva009A9070Source *)value, *(int *)((char *)context + 0x254));
        Rva009A9070CopyStreams(*(Rva009A9070Context **)((char *)context + 0x298), (Rva009A9070Source *)value, *(int *)((char *)context + 0x24c));
        return;
    case 0:
        if (value == 9) { value = 70; selector = 1; goto again; }
        *(int *)((char *)context + 0x1a0) = value;
        *(int *)((char *)context + 0x1a8) = 0;
        return;
    case 8: *(int *)((char *)context + 0x4944) = value; return;
    case 5: *(int *)((char *)context + 0x493c) = value; return;
    case 6: *(int *)((char *)context + 0x4940) = value; return;
    default: return;
    }
}
