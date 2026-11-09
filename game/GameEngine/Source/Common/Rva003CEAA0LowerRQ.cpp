// Retail 0x003CEAA0, 37 bytes. The wrapper constructs the one-byte
// comparator also used by Rva003D0190::ensure, then forwards three pointers
// to the pinned lower-bound helper. Only a generated thunk names the entry,
// so the function keeps its retail address in the name.
struct BfmeCmpRQ
{
    char m_bfmeRawRQ;
};

// Retail calls ILT 0x00016B21, which the ledger defines as ?j_00016b21@@YAXXZ.
extern void j_00016b21();
typedef void ** (__cdecl *BfmeLowerRQCall)(void **begin, void **end, void **key,
                                           BfmeCmpRQ compare, int spare);

void ** __cdecl Rva003CEAA0LowerRQ(void **begin, void **end, void **key)
{
    BfmeCmpRQ compare;
    compare.m_bfmeRawRQ = 0;
    return ((BfmeLowerRQCall)j_00016b21)(begin, end, key, compare, 0);
}
