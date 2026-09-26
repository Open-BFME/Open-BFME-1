// Retail at 0x00609F50 stores 1 in the byte at this+0x15 and returns.
// The owning type and field semantics were not recovered.
struct Rva00609F50ByteSetter
{
    unsigned char m_pad[0x15];
    unsigned char m_value;

    void set();
};

void Rva00609F50ByteSetter::set()
{
    m_value = 1;
}
