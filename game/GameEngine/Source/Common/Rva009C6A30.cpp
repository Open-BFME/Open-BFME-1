// cl: /DNDEBUG /MD /O2
extern const unsigned short Rva012D88D0Round[4];
extern void __cdecl rva009C6390BinkMmx(const void *, void *, int, int, int, int, const void *);
extern void __cdecl rva009C66F0BinkMmx(const void *, void *, int, int, int, int, const void *);
extern void __cdecl rva009C6470BinkMmx(const void *, void *, int, int, int, int, const void *);
extern void __cdecl rva009C6780BinkMmx(const void *, void *, int, int, int, int, const void *);
extern void __cdecl rva009C69D0BinkMmx(const void *, void *, int, const void *, const void *);
extern void __cdecl Rva009C6800(const unsigned char *, unsigned char *, int, const void *, const void *);
extern void __cdecl bfmeUnpack8to16Mmx(const void *, void *, int);

void __cdecl Rva009C6A30(void *arg1, void *arg2, void *arg3,
    int stride, int weightsA, int weightsB, int mode)
{
    unsigned char scratch[256];
    int distance = (int)arg2 - (int)arg1;
    if (distance < 0)
    {
        void *temporary = arg1;
        arg1 = arg2;
        arg2 = temporary;
        distance = (int)arg2 - (int)arg1;
    }
    if (distance == 0)
        return;

    if (distance == 1)
    {
        if (mode != 0)
            rva009C6390BinkMmx(arg1, scratch, stride, distance, 8, 8,
                (const void *)((const unsigned char *)Rva012D88D0Round + 0x110 + (weightsA << 6)));
        else
            rva009C66F0BinkMmx(arg1, scratch, stride, 1, 8, 8,
                (const void *)((const unsigned char *)Rva012D88D0Round + 0x10 + (weightsA << 5)));
    }
    else if (distance == stride)
    {
        if (mode != 0)
            rva009C6470BinkMmx(arg1, scratch, stride, stride, 8, 8,
                (const void *)((const unsigned char *)Rva012D88D0Round + 0x110 + (weightsB << 6)));
        else
            rva009C6780BinkMmx(arg1, scratch, stride, stride, 8, 8,
                (const void *)((const unsigned char *)Rva012D88D0Round + 0x10 + (weightsB << 5)));
    }
    else if (distance == stride - 1)
    {
        if (mode != 0)
            rva009C69D0BinkMmx((const unsigned char *)arg1 - 1, scratch, stride,
                (const void *)((const unsigned char *)Rva012D88D0Round + 0x110 + (weightsA << 6)),
                (const void *)((const unsigned char *)Rva012D88D0Round + 0x110 + (weightsB << 6)));
        else
            Rva009C6800((const unsigned char *)arg1 - 1, scratch, stride,
                (const void *)((const unsigned char *)Rva012D88D0Round + 0x10 + (weightsA << 5)),
                (const void *)((const unsigned char *)Rva012D88D0Round + 0x10 + (weightsB << 5)));
    }
    else if (distance == stride + 1)
    {
        if (mode != 0)
            rva009C69D0BinkMmx(arg1, scratch, stride,
                (const void *)((const unsigned char *)Rva012D88D0Round + 0x110 + (weightsA << 6)),
                (const void *)((const unsigned char *)Rva012D88D0Round + 0x110 + (weightsB << 6)));
        else
            Rva009C6800((const unsigned char *)arg1, scratch, stride,
                (const void *)((const unsigned char *)Rva012D88D0Round + 0x10 + (weightsA << 5)),
                (const void *)((const unsigned char *)Rva012D88D0Round + 0x10 + (weightsB << 5)));
    }
    bfmeUnpack8to16Mmx(scratch, arg3, 8);
}
