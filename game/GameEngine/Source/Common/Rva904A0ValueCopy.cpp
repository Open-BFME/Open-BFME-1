class Rva904A0ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_000904a0@@YAXXZ
unsigned int *Rva904A0ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
