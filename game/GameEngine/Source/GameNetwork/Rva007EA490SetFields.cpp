// cl: /O2
// Set three adjacent dwords at +0x224..+0x22C of the nested state.
struct Rva007EA490Inner
{
    char m_prefix[0x224];
    int m_first;
    int m_second;
    int m_third;
};

struct Rva007EA490Owner
{
    int m_reserved;
    Rva007EA490Inner *m_inner;
    void set(int first, int second, int third);
};

void Rva007EA490Owner::set(int first, int second, int third)
{
    m_inner->m_first = first;
    m_inner->m_second = second;
    m_inner->m_third = third;
}
