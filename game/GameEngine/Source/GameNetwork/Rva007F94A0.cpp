// The owner identity for this thiscall search is unproven; retain the RVA.
struct Rva007F94A0Record
{
    void *m_key;
    char m_rest[0x18];
};

class Rva007F94A0Owner
{
public:
    Rva007F94A0Record *rva007F94A0(void *key);

private:
    char m_padding[0x28];
    Rva007F94A0Record m_records[0x20];
};

Rva007F94A0Record *Rva007F94A0Owner::rva007F94A0(void *key)
{
    int i = 0;
    Rva007F94A0Record *slot = m_records;
    for (; i < 0x20; ++i, ++slot)
        if (slot->m_key == key)
            return slot;
    return 0;
}
