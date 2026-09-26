class Rva13EFC0ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_0013efc0@@YAXXZ
unsigned int *Rva13EFC0ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
