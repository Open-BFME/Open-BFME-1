class Rva629C0ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_000629c0@@YAXXZ
unsigned int *Rva629C0ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
