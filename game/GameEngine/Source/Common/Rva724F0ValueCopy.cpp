class Rva724F0ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_000724f0@@YAXXZ
unsigned int *Rva724F0ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
