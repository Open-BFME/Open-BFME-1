class Rva92B60ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_00092b60@@YAXXZ
unsigned int *Rva92B60ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
