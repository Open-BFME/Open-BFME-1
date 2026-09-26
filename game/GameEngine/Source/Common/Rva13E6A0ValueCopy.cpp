class Rva13E6A0ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_0013e6a0@@YAXXZ
unsigned int *Rva13E6A0ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
