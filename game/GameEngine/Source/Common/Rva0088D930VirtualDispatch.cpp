// Open-BFME: constant virtual dispatch reconstructed from retail RVA 0x0088D930.

class Rva0088D930Object
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
    virtual void unused8(void);
    virtual void unused9(void);
    virtual void unused10(void);
    virtual void unused11(void);
    virtual void unused12(void);
    virtual void unused13(void);
    virtual void unused14(void);
    virtual void unused15(void);
    virtual void unused16(void);
    virtual void unused17(void);
    virtual void unused18(void);
    virtual void unused19(void);
    virtual void dispatch(const void *first, int second);

    Rva0088D930Object *invoke(int unused);
};

Rva0088D930Object *Rva0088D930Object::invoke(int unused)
{
    dispatch(reinterpret_cast<const void *>(0x01134280u), 2);
    return this;
}
