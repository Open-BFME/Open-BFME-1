class Rva6E3B0ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_0006e3b0@@YAXXZ
unsigned int *Rva6E3B0ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
