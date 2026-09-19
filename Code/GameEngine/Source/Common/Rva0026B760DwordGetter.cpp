// cl: /O2 /Ob0

// Retail reads one dword at this plus four and returns it.
// No caller or vtable evidence proves the owning type, so the name stays address-derived.
struct Rva0026B760DwordGetter
{
    char m_prefix[4];
    unsigned int m_value;

    unsigned int get() const;
};

unsigned int Rva0026B760DwordGetter::get() const
{
    return m_value;
}
