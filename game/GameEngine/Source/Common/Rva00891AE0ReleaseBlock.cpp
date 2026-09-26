// cl: /O2 /MD

struct BfmeStringData3AF0
{
    unsigned short m_refCount;
};

struct BfmeStringPool3AF0
{
    void *m_unused;
    void (__cdecl *free)(void *storage);
};

extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

void bfmeRva00891AE0ReleaseBlock(BfmeStringData3AF0 *block)
{
    if (--block->m_refCount == 0)
        g_bfmeStringPool1284->free(block);
}
