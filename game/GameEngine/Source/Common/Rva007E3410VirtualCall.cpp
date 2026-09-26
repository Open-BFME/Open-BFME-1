// Open-BFME: mode-gated virtual call reconstructed from retail RVA 0x007E3410.

class Rva007E3410Target
{
public:
    virtual void unused0(void);
    virtual void unused1(void);
    virtual void unused2(void);
    virtual void unused3(void);
    virtual void unused4(void);
    virtual void invoke(int first, int second);
};

class Rva007E3410Object
{
public:
    void invokeForMode(void);

private:
    char m_pad0[4];
    Rva007E3410Target *m_target;
    int m_mode;
};

void Rva007E3410Object::invokeForMode(void)
{
    if (m_mode == 6)
    {
        m_target->invoke(0, 0);
    }
}
