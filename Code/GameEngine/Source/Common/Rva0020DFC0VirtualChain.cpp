// Open-BFME: two-stage virtual call reconstructed from retail RVA 0x0020DFC0.

class Rva0020DFC0Object
{
public:
    virtual void unused0(void);
    virtual void unused1(void);
    virtual void unused2(void);
    virtual void unused3(void);
    virtual void unused4(void);
    virtual void unused5(void);
    virtual void unused6(void);
    virtual void unused7(void);
    virtual int first(void);
    virtual void second(int value);

    void invoke(void);
};

void Rva0020DFC0Object::invoke(void)
{
    int value = first();
    second(value);
}
