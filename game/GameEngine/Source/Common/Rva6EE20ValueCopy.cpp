class Rva6EE20ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_0006ee20@@YAXXZ
unsigned int *Rva6EE20ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
