class Rva13D260MemberAddress {
public:
    unsigned char *member();

private:
    unsigned char m_prefix[0x2B8];
    unsigned char m_member;
};

// ?d_0013d260@@YAXXZ
unsigned char *Rva13D260MemberAddress::member()
{
    return &m_member;
}
