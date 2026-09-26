class Rva1262D0ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_001262d0@@YAXXZ
unsigned int *Rva1262D0ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
