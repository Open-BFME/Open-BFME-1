// Retail at 0x00267FE0 clears the byte at this+0x14 and returns.
// The owning type and field semantics were not recovered.
struct Rva00267FE0ByteClear
{
    unsigned char m_pad[0x14];
    unsigned char m_value;

    void clear();
};

void Rva00267FE0ByteClear::clear()
{
    m_value = 0;
}
