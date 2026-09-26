// Retail at 0x00695A70 stores 1 in the byte at this+0x47 and returns.
// The owning type and field semantics were not recovered.
struct Rva00695A70ByteSetter
{
    unsigned char m_pad[0x47];
    unsigned char m_value;

    void set();
};

void Rva00695A70ByteSetter::set()
{
    m_value = 1;
}
