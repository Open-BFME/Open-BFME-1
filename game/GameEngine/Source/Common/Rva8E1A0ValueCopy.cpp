class Rva8E1A0ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_0008e1a0@@YAXXZ
unsigned int *Rva8E1A0ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
