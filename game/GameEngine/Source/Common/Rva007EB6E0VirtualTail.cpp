// cl: /O2
// 0x007EB6E0: call slot 1 then forward through the result's +0x6A8 member.
class Rva007EB6E0Object
{
public:
    virtual Rva007EB6E0Object *unused0(void);
    virtual Rva007EB6E0Object *advance(void);
    void invoke(void);
private:
    char m_pad0[0x6A4];
    Rva007EB6E0Object *m_next;
};

void Rva007EB6E0Object::invoke(void)
{
    Rva007EB6E0Object *result = advance();
    result->m_next->advance();
}
