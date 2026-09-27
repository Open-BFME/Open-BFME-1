// ?Rva009C7380@@YAXPAX00HHHH@Z
// partial score=0.86 date=2026-09-27
// cl: /DNDEBUG /MD /O2
// Address-derived body Rva009C7380; the owner and exact global table name remain unproved.
// The four 0x12D8C10 bases are retail immediates used for 32-byte coefficient rows.
extern void __cdecl rva009C7060BinkSse(const void *, void *, int, int, int, int, const void *);
extern void __cdecl rva009C70D0BinkSse(const void *, void *, int, int, int, int, const void *);
extern void __cdecl rva009C7140BinkSse(const void *, void *, int, const void *, const void *);

void __cdecl Rva009C7380(
    void *first,
    void *second,
    void *destination,
    int stride,
    int adjacentWeights,
    int verticalWeights,
    int diagonalWeights)
{
    int difference = (int)((unsigned int)second - (unsigned int)first);
    if (difference < 0)
    {
        difference = (int)((unsigned int)first - (unsigned int)second);
        first = second;
    }

    if (difference == 1)
    {
        rva009C7060BinkSse(first, destination, stride, 1, 8, 8,
            reinterpret_cast<const void *>(0x012D8C10 + ((unsigned int)adjacentWeights << 5)));
        return;
    }
    if (difference == stride)
    {
        rva009C70D0BinkSse(first, destination, stride, stride, 8, 8,
            reinterpret_cast<const void *>(0x012D8C10 + ((unsigned int)verticalWeights << 5)));
        return;
    }
    if (difference == stride - 1)
    {
        rva009C7140BinkSse((const unsigned char *)first - 1, destination, stride,
            reinterpret_cast<const void *>(0x012D8C10 + ((unsigned int)adjacentWeights << 5)),
            reinterpret_cast<const void *>(0x012D8C10 + ((unsigned int)verticalWeights << 5)));
        return;
    }
    if (difference == stride + 1)
    {
        rva009C7140BinkSse(first, destination, stride,
            reinterpret_cast<const void *>(0x012D8C10 + ((unsigned int)adjacentWeights << 5)),
            reinterpret_cast<const void *>(0x012D8C10 + ((unsigned int)verticalWeights << 5)));
    }
}
