// Retail at 0x004104B0 stores 2 in the byte at this+0x38 and returns.
// The owning type and field semantics were not recovered.
struct Rva004104B0ByteSetter
{
    unsigned char m_pad[0x38];
    unsigned char m_value;

    void set();
};

void Rva004104B0ByteSetter::set()
{
    m_value = 2;
}
