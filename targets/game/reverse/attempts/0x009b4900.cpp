// ?Rva009B4900@@YAIPAURva009B4900Reader@@PBTRva009B4900Prefix@@PBURva009B4900Node@@@Z
// partial score=0.977695 date=2026-09-28
// cl: /O2 /Ob1 /DNDEBUG /MD
// Retail 009B4900..009B4A0C: INT3-delimited bitstream tree decoder.
// It uses MSVC's private static-function convention, not a public cdecl ABI.
struct Rva009B4900Reader {
    unsigned remaining;
    unsigned word;
    const unsigned char *next;
};
union Rva009B4900Prefix {
    unsigned short raw;
    struct { unsigned short leaf:1, value:5, unused:6, bits:4; } code;
};
union Rva009B4900Code {
    unsigned raw;
    struct { unsigned leaf:1, value:7, unused:24; } code;
};
struct Rva009B4900Node {
    Rva009B4900Code child[2];
    unsigned unused;
};
static unsigned Rva009B4900(Rva009B4900Reader *reader,
    const Rva009B4900Prefix *prefix, const Rva009B4900Node *tree)
{
    unsigned bits = reader->word & ((1U << reader->remaining) - 1);
    unsigned look;
    if (reader->remaining >= 6)
        look = bits >> (reader->remaining - 6);
    else
        look = ((bits << 8) | *reader->next) >> (reader->remaining + 2);
    reader->remaining -= prefix[look].code.bits;
    if ((int)reader->remaining < 0) {
        const unsigned char *p = reader->next;
        reader->word = ((p[0] * 256U + p[1]) * 256U + p[2]) * 256U + p[3];
        reader->next += 4;
        reader->remaining += 32;
    }
    if (prefix[look].code.leaf) return prefix[look].code.value;
    Rva009B4900Code code;
    code.code.value = prefix[look].code.value;
    do {
        unsigned bit;
        if (reader->remaining) {
            --reader->remaining;
            bit = (reader->word >> reader->remaining) & 1;
        } else {
            const unsigned char *p = reader->next;
            reader->word = ((p[0] * 256U + p[1]) * 256U + p[2]) * 256U + p[3];
            reader->next += 4;
            reader->remaining = 31;
            bit = reader->word >> 31;
        }
        if (bit) code = tree[code.code.value].child[1];
        else code = tree[code.code.value].child[0];
    } while (!code.code.leaf);
    return code.code.value;
}

// Absent-from-retail integration entry; keeps the private helper emitted.
unsigned Rva009B4900Call(Rva009B4900Reader *reader,
    const Rva009B4900Prefix *prefix, const Rva009B4900Node *tree)
{
    return Rva009B4900(reader, prefix, tree);
}
