class Rva13E7B0ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_0013e7b0@@YAXXZ
unsigned int *Rva13E7B0ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
