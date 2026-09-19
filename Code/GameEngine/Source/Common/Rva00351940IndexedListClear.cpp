// cl: /O2

// Retail 0x00351940 clears the byte at offset 0x0C in each 20-byte entry
// then follows the entry's first dword until it reaches -1.
struct Rva00351940Owner
{
    char m_padding00[0x0c];
    unsigned int m_entries;
    char m_padding10[0x0c];
    int m_index;

    void clearEntries();
};

static __forceinline void rva00351940Clear(unsigned int offset, unsigned int pointer)
{
    *(unsigned char *)(offset + pointer) = 0;
}

static __forceinline int rva00351940Read(unsigned int offset, unsigned int pointer)
{
    return *(int *)(offset + pointer);
}

void Rva00351940Owner::clearEntries()
{
    int index = m_index;
    if (index == -1)
        return;

    do
    {
        rva00351940Clear((unsigned int)(index * 20 + 0x0c), m_entries);
        index = rva00351940Read((unsigned int)(index * 20), m_entries);
    }
    while (index != -1);
}
