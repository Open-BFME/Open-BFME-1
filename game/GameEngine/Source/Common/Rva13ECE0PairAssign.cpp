class Rva13ECE0PairAssign
{
public:
    Rva13ECE0PairAssign *assign(const unsigned int *value, const unsigned char *flag);

private:
    unsigned int m_value;
    unsigned char m_flag;
};

// ?d_0013ece0@@YAXXZ
Rva13ECE0PairAssign *Rva13ECE0PairAssign::assign(const unsigned int *value, const unsigned char *flag)
{
    m_value = *value;
    m_flag = *flag;
    return this;
}
