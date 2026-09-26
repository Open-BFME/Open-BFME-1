class Rva13ED70PairAssign
{
public:
    Rva13ED70PairAssign *assign(const unsigned int *value, const unsigned char *flag);

private:
    unsigned int m_value;
    unsigned char m_flag;
};

// ?d_0013ed70@@YAXXZ
Rva13ED70PairAssign *Rva13ED70PairAssign::assign(const unsigned int *value, const unsigned char *flag)
{
    m_value = *value;
    m_flag = *flag;
    return this;
}
