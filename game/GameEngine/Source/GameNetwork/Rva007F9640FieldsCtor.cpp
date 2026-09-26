// cl: /O2
// Seven words are reset, beginning at +4 then +0.
class Rva007F9640Fields
{
public:
    Rva007F9640Fields();
private:
    unsigned int m_zero;
    unsigned int m_first;
    unsigned int m_second;
    unsigned int m_third;
    unsigned int m_fourth;
    unsigned int m_fifth;
    unsigned int m_sixth;
};

Rva007F9640Fields::Rva007F9640Fields()
{
    m_first = 0;
    m_zero = 0;
    m_second = 0;
    m_third = 0;
    m_fourth = 0;
    m_fifth = 0;
    m_sixth = 0;
}
