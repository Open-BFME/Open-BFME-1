// Open-BFME: virtual tail-call chain reconstructed from retail RVA 0x007EB6F0.

class Rva007EB6F0Object
{
public:
    virtual Rva007EB6F0Object *unused0(void);
    virtual Rva007EB6F0Object *advance(void);
    virtual void unused2(void);
    virtual void tail(void);

    void invoke(void);

private:
    char m_pad0[0x6A4];
    Rva007EB6F0Object *m_next;
};

void Rva007EB6F0Object::invoke(void)
{
    Rva007EB6F0Object *result = advance();
    result->m_next->tail();
}
