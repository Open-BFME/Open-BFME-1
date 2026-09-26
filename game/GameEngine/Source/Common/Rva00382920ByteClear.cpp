// Retail at 0x00382920 clears the byte at this+0x0C and returns.
// The owning type and field semantics were not recovered.
struct Rva00382920ByteClear
{
    unsigned char m_pad[0x0C];
    unsigned char m_value;

    void clear();
};

void Rva00382920ByteClear::clear()
{
    m_value = 0;
}
