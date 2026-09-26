class Rva6E3C0ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_0006e3c0@@YAXXZ
unsigned int *Rva6E3C0ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
