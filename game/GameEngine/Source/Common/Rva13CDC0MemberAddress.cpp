class Rva13CDC0MemberAddress
{
public:
    unsigned char *member();

private:
    unsigned char m_prefix[0xA4];
    unsigned char m_value;
};

unsigned char *Rva13CDC0MemberAddress::member()
{
    return &m_value;
}
