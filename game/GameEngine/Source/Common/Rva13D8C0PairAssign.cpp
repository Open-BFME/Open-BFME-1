class Rva13D8C0PairAssign
{
public:
    Rva13D8C0PairAssign *assign(const unsigned int *value, const unsigned char *flag);

private:
    unsigned int m_value;
    unsigned char m_flag;
};

Rva13D8C0PairAssign *Rva13D8C0PairAssign::assign(const unsigned int *value, const unsigned char *flag)
{
    m_value = *value;
    m_flag = *flag;
    return this;
}
