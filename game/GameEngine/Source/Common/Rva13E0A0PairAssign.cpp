class Rva13E0A0PairAssign
{
public:
    Rva13E0A0PairAssign *assign(const unsigned int *value, const unsigned char *flag);

private:
    unsigned int m_value;
    unsigned char m_flag;
};

// ?d_0013e0a0@@YAXXZ
Rva13E0A0PairAssign *Rva13E0A0PairAssign::assign(const unsigned int *value, const unsigned char *flag)
{
    m_value = *value;
    m_flag = *flag;
    return this;
}
