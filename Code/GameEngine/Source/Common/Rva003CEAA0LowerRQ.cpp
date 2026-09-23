// Retail 0x003CEAA0, 37 bytes. The wrapper constructs the one-byte
// comparator also used by Rva003D0190::ensure, then forwards three pointers
// to the pinned lower-bound helper. Only a generated thunk names the entry,
// so the function keeps its retail address in the name.
struct BfmeCmpRQ
{
    char m_bfmeRawRQ;
};

extern void ** __cdecl bfmeLowerRQ(void **begin, void **end, void **key,
                                   BfmeCmpRQ compare, int spare);

void ** __cdecl Rva003CEAA0LowerRQ(void **begin, void **end, void **key)
{
    BfmeCmpRQ compare;
    compare.m_bfmeRawRQ = 0;
    return bfmeLowerRQ(begin, end, key, compare, 0);
}
