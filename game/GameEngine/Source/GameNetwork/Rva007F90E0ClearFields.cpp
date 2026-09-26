// cl: /O2
// 0x007F90E0 clears seven consecutive four-byte fields, second before first.
struct Rva007F90E0Fields
{
    unsigned int m_zero;
    unsigned int m_first;
    unsigned int m_second;
    unsigned int m_third;
    unsigned int m_fourth;
    unsigned int m_fifth;
    unsigned int m_sixth;
    void clear();
};

void Rva007F90E0Fields::clear()
{
    m_first = 0;
    m_zero = 0;
    m_second = 0;
    m_third = 0;
    m_fourth = 0;
    m_fifth = 0;
    m_sixth = 0;
}
