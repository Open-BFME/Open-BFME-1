class Rva13D250MemberAddress {
public:
    unsigned char *member();

private:
    unsigned char m_prefix[0x2AC];
    unsigned char m_member;
};

// ?d_0013d250@@YAXXZ
unsigned char *Rva13D250MemberAddress::member()
{
    return &m_member;
}
