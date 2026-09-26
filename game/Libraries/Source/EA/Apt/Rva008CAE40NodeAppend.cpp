// cl: /DNDEBUG /MD /EHsc

struct Rva008CAE40RefBlock
{
    unsigned short m_refs;
};

class Rva008B2EA0Node
{
public:
    virtual void Release();

    bool GetMaxRefCountHit() const
    {
        return (m_flags >> 30 & 1) != 0;
    }

    unsigned m_flags;
    Rva008CAE40RefBlock *m_block;
};

class Rva008CAE40Array
{
public:
    int m_count;
    char m_gap04[4];
    Rva008B2EA0Node **m_values;
};

extern Rva008B2EA0Node *rva008B2EA0Create();
extern Rva008CAE40RefBlock *g_rva008CAE40DefaultBlock;
extern void (__cdecl **Rva01337A30ReleaseTable)(void *);

void rva008CAE40NodeAppend(Rva008CAE40Array *array)
{
    Rva008B2EA0Node *node = rva008B2EA0Create();

    ++g_rva008CAE40DefaultBlock->m_refs;
    Rva008CAE40RefBlock *old_block = node->m_block;
    --old_block->m_refs;
    if (old_block->m_refs == 0)
        Rva01337A30ReleaseTable[1](old_block);
    node->m_block = g_rva008CAE40DefaultBlock;

    array->m_values[array->m_count] = node;
    ++array->m_count;

    if (!node->GetMaxRefCountHit())
        node->Release();
}
