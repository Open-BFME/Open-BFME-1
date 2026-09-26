// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// RVA 0x009AB950: select one 128-byte block and copy two short values.
struct Rva009AB950Context
{
    int m_unused;
    const unsigned short *m_wordTable;
    unsigned int m_wordIndex;
    void *m_blocks[1];
};

struct Rva009AB950Output
{
    unsigned char m_unused[4];
    void *m_block;
    unsigned short m_reference;
    unsigned short m_current;
};

extern const unsigned short Rva01142BA0Table[];

void __cdecl Rva009AB950Select(Rva009AB950Context *context,
                               Rva009AB950Output *output, unsigned int block)
{
    output->m_block = context->m_blocks[block];
    output->m_current = context->m_wordTable[block * 64];
    output->m_reference = Rva01142BA0Table[context->m_wordIndex * 2];
}
