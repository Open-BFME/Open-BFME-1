class Rva72510ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_00072510@@YAXXZ
unsigned int *Rva72510ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
