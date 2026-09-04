// cl: /DNDEBUG /MD /EHsc

struct Rva008CAEA0RefBlock
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
    Rva008CAEA0RefBlock *m_block;
};

class Rva008CAEA0Array
{
public:
    int m_count;
    char m_gap04[4];
    Rva008B2EA0Node **m_values;
};

extern Rva008B2EA0Node *rva008B2EA0Create();
extern Rva008CAEA0RefBlock *g_rva008CAEA0DefaultBlock;
extern void (__cdecl **Rva01337A30ReleaseTable)(void *);

void rva008CAEA0NodeAppend(Rva008CAEA0Array *array)
{
    Rva008B2EA0Node *node = rva008B2EA0Create();

    ++g_rva008CAEA0DefaultBlock->m_refs;
    Rva008CAEA0RefBlock *old_block = node->m_block;
    --old_block->m_refs;
    if (old_block->m_refs == 0)
        Rva01337A30ReleaseTable[1](old_block);
    node->m_block = g_rva008CAEA0DefaultBlock;

    array->m_values[array->m_count] = node;
    ++array->m_count;

    if (!node->GetMaxRefCountHit())
        node->Release();
}
