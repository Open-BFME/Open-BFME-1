class Rva13E0E0PairAssign
{
public:
    Rva13E0E0PairAssign *assign(const unsigned int *value, const unsigned char *flag);

private:
    unsigned int m_value;
    unsigned char m_flag;
};

// ?d_0013e0e0@@YAXXZ
Rva13E0E0PairAssign *Rva13E0E0PairAssign::assign(const unsigned int *value, const unsigned char *flag)
{
    m_value = *value;
    m_flag = *flag;
    return this;
}
