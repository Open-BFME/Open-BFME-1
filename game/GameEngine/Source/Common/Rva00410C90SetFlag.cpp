// cl: /O2 /DNDEBUG /MD
// Retail receiver has a virtual result accessor in slot 10; the result owns flags at +0x110.
struct Rva00410C90Result
{
    unsigned char m_beforeFlags[0x110];
    unsigned int m_flags;
};

struct Rva00410C90Provider
{
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual Rva00410C90Result *getResult();
};

int rva00410C90SetFlag(Rva00410C90Provider *provider)
{
    if (provider)
    {
        Rva00410C90Result *result = provider->getResult();
        if (result)
            result->m_flags |= 0x40;
    }
    return 1;
}
