class Rva64760ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_00064760@@YAXXZ
unsigned int *Rva64760ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
