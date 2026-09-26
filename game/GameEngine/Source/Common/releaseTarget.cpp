// Open-BFME: flagged-pointer release reconstructed from retail RVA 0x0089C720.

class Rva0089C720Target
{
public:
    virtual void unused0(void);
    virtual void release(void);
};

class Rva0089C720Holder
{
public:
    char m_pad0[4];
    unsigned int m_flaggedTarget;
};

void releaseTarget(Rva0089C720Holder *holder)
{
    Rva0089C720Target *target = reinterpret_cast<Rva0089C720Target *>(holder->m_flaggedTarget & ~1u);
    target->release();
    holder->m_flaggedTarget = 0;
}
