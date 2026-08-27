// Open-BFME: pointer release reconstructed from retail RVA 0x008A0570.

class Rva008A0570Target
{
public:
    virtual void unused0(void);
    virtual void release(void);
};

class Rva008A0570Object
{
public:
    void releaseTarget(void);

private:
    char m_pad0[0x7C];
    Rva008A0570Target *m_target;
};

void Rva008A0570Object::releaseTarget(void)
{
    m_target->release();
    m_target = 0;
}
