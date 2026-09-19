// cl: /DNDEBUG /MD /EHsc

struct PairRva003C5F20PairAssign
{
    unsigned int m_first;
    unsigned int m_second;
};

class Rva003C5F20PairAssign
{
public:
    void set(const PairRva003C5F20PairAssign &value);

private:
    char m_lead[0xbc];
    unsigned int m_first;
    unsigned int m_second;
};

void Rva003C5F20PairAssign::set(const PairRva003C5F20PairAssign &value)
{
    m_first = value.m_first;
    m_second = value.m_second;
}
