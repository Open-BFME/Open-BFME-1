class Rva13A440MemberAddress
{
public:
    unsigned char *member();

private:
    unsigned char m_prefix[0x2A0];
    unsigned char m_value;
};

// ?d_0013a440@@YAXXZ
unsigned char *Rva13A440MemberAddress::member()
{
    return &m_value;
}
