class Rva13D180SecondMemberAddress {
public:
    unsigned int *second(unsigned int ignored);

private:
    unsigned int m_first;
    unsigned int m_second;
};

// ?d_0013d180@@YAXXZ
unsigned int *Rva13D180SecondMemberAddress::second(unsigned int)
{
    return &m_second;
}
