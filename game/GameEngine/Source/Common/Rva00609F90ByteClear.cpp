// Retail at 0x00609F90 clears the byte at this+0x15 and returns.
// The owning type and field semantics were not recovered.
struct Rva00609F90ByteClear
{
    unsigned char m_pad[0x15];
    unsigned char m_value;

    void clear();
};

void Rva00609F90ByteClear::clear()
{
    m_value = 0;
}
