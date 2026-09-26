// cl: /O2

// Retail 0x00351910 marks the byte at offset 0x0C in each 20-byte entry,
// then follows the entry's first dword until it reaches -1.
struct Rva00351910Entry
{
    int m_next;
    char m_padding[8];
    unsigned char m_marked;
    char m_tail[7];
};

struct Rva00351910Owner
{
    char m_padding00[0x0c];
    unsigned int m_entries;
    char m_padding10[0x0c];
    int m_index;

    void markEntries();
};

static __forceinline void rva00351910Mark(unsigned int offset, unsigned int pointer)
{
    *(unsigned char *)(offset + pointer) = 1;
}

static __forceinline int rva00351910Read(unsigned int offset, unsigned int pointer)
{
    return *(int *)(offset + pointer);
}

void Rva00351910Owner::markEntries()
{
    int index = m_index;
    if (index == -1)
        return;

    do
    {
        rva00351910Mark((unsigned int)(index * 20 + 0x0c), m_entries);
        index = rva00351910Read((unsigned int)(index * 20), m_entries);
    }
    while (index != -1);
}
