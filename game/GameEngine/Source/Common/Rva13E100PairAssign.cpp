class Rva13E100PairAssign
{
public:
    Rva13E100PairAssign *assign(const unsigned int *value, const unsigned char *flag);

private:
    unsigned int m_value;
    unsigned char m_flag;
};

// ?d_0013e100@@YAXXZ
Rva13E100PairAssign *Rva13E100PairAssign::assign(const unsigned int *value, const unsigned char *flag)
{
    m_value = *value;
    m_flag = *flag;
    return this;
}
