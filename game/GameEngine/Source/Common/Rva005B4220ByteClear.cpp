// Retail at 0x005B4220 clears the byte at this+0x1C and returns.
// The owning type and field semantics were not recovered.
struct Rva005B4220ByteClear
{
    unsigned char m_pad[0x1C];
    unsigned char m_value;

    void clear();
};

void Rva005B4220ByteClear::clear()
{
    m_value = 0;
}
