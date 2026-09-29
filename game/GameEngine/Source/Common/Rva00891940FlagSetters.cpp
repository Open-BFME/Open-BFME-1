// cl: /O2 /MD

class Rva00891940Flags
{
    unsigned m_unused;
    unsigned m_flags;

public:
    void setBit15(int on);
    void setBit14(bool on);
    void setField6(unsigned value);
};

void Rva00891940Flags::setBit15(int on)
{
    m_flags &= ~0x8000U;
    if (on)
        m_flags |= 0x8000U;
}

void Rva00891940Flags::setBit14(bool on)
{
    m_flags &= ~0x4000U;
    if (on)
        m_flags |= 0x4000U;
}

void Rva00891940Flags::setField6(unsigned value)
{
    if (value == 0)
    {
        m_flags &= ~0x3FC0U;
        return;
    }
    m_flags = (m_flags & ~0x3FC0U) | (value << 6);
}
