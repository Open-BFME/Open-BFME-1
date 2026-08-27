// Open-BFME: guarded counter decrements reconstructed from retail RVAs
// 0x00695DC0 and 0x00695DE0.

class Rva00695DC0Counter
{
public:
    void decrement(void);

private:
    char m_pad0[0x610];
    unsigned int m_count;
};

class Rva00695DE0Counter
{
public:
    void decrement(void);

private:
    char m_pad0[0x614];
    unsigned int m_count;
};

void Rva00695DC0Counter::decrement(void)
{
    if (m_count > 0)
    {
        --m_count;
    }
}

void Rva00695DE0Counter::decrement(void)
{
    if (m_count > 0)
    {
        --m_count;
    }
}
