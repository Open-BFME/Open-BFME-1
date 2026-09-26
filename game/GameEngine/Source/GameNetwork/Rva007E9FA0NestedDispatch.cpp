class Rva007E9FA0Inner
{
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
};

struct Rva007E9FA0Nested
{
    char m_padding[0x6A8];
    Rva007E9FA0Inner *m_inner;
};

class Rva007E9FA0Owner
{
public:
    void dispatch();
private:
    char m_padding[0x254];
    Rva007E9FA0Nested *m_nested;
};

void Rva007E9FA0Owner::dispatch()
{
    m_nested->m_inner->slot2();
}
