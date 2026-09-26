// ?d_007f94a0@@YAXXZ
// partial score=0.67 date=2026-09-26
// cl: /O2
// Search 32 embedded 28-byte records by their leading key.
struct Rva007F94A0Record
{
    void *m_key;
    char m_rest[24];
};

struct Rva007F94A0Owner
{
    char m_pad[0x28];
    Rva007F94A0Record m_records[32];
    Rva007F94A0Record *find(void *key);
};

Rva007F94A0Record *Rva007F94A0Owner::find(void *key)
{
    Rva007F94A0Record *slot = m_records;
    for (int i = 0; i < 32; ++i, ++slot)
        if (slot->m_key == key)
            return slot;
    return 0;
}
