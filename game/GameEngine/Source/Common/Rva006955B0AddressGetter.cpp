// cl: /O2

struct Rva006955B0AddressGetter
{
    char m_prefix[0x14];

    void *get() const;
};

void *Rva006955B0AddressGetter::get() const
{
    return (void *)((char *)this + 0x14);
}
