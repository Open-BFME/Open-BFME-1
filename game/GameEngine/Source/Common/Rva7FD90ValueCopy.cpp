class Rva7FD90ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_0007fd90@@YAXXZ
unsigned int *Rva7FD90ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
