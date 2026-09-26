// Open-BFME: virtual getter comparison reconstructed from retail RVA 0x002857B0.

class Rva002857B0Target
{
public:
    virtual void unused0(void);
    virtual void unused1(void);
    virtual void unused2(void);
    virtual void unused3(void);
    virtual void unused4(void);
    virtual void unused5(void);
    virtual int getValue(void);
};

class Rva002857B0Object
{
public:
    bool equals(int value);

private:
    char m_pad0[0x18];
    Rva002857B0Target *m_target;
};

bool Rva002857B0Object::equals(int value)
{
    return value == m_target->getValue();
}
