// Retail at 0x001BDCE0 stores 1 in the byte at this+0x2C and returns.
// The owning type and field semantics were not recovered.
struct Rva001BDCE0ByteSetter
{
    unsigned char m_pad[0x2C];
    unsigned char m_value;

    void set();
};

void Rva001BDCE0ByteSetter::set()
{
    m_value = 1;
}
