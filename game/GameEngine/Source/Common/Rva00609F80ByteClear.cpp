// Retail at 0x00609F80 clears the byte at this+0x14 and returns.
// The owning type and field semantics were not recovered.
struct Rva00609F80ByteClear
{
    unsigned char m_pad[0x14];
    unsigned char m_value;

    void clear();
};

void Rva00609F80ByteClear::clear()
{
    m_value = 0;
}
