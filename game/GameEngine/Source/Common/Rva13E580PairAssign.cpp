class Rva13E580PairAssign
{
public:
    Rva13E580PairAssign *assign(const unsigned int *value, const unsigned char *flag);

private:
    unsigned int m_value;
    unsigned char m_flag;
};

// ?d_0013e580@@YAXXZ
Rva13E580PairAssign *Rva13E580PairAssign::assign(const unsigned int *value, const unsigned char *flag)
{
    m_value = *value;
    m_flag = *flag;
    return this;
}
