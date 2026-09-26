// cl: /O2 /MD

class Rva00891920Flags
{
    unsigned m_unused;
    unsigned m_rva00891920Flags;

public:
    void setRva00891920LowBits(unsigned bits);
};

void Rva00891920Flags::setRva00891920LowBits(unsigned bits)
{
    m_rva00891920Flags = (m_rva00891920Flags & ~0x3fU) | bits;
}
