// Open-BFME: virtual tail-call chain reconstructed from retail RVA 0x007EB700.

class Rva007EB700Object
{
public:
    virtual Rva007EB700Object *unused0(void);
    virtual Rva007EB700Object *advance(void);
    virtual void unused2(void);
    virtual void unused3(void);
    virtual void tail(void);

    void invoke(void);

private:
    char m_pad0[0x6A4];
    Rva007EB700Object *m_next;
};

void Rva007EB700Object::invoke(void)
{
    Rva007EB700Object *result = advance();
    result->m_next->tail();
}
