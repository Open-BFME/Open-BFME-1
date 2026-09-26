// Retail at 0x00695A80 clears the byte at this+0x47 and returns.
// The owning type and field semantics were not recovered.
struct Rva00695A80ByteClear
{
    unsigned char m_pad[0x47];
    unsigned char m_value;

    void clear();
};

void Rva00695A80ByteClear::clear()
{
    m_value = 0;
}
