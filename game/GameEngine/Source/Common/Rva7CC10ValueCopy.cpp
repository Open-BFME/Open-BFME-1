class Rva7CC10ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_0007cc10@@YAXXZ
unsigned int *Rva7CC10ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
