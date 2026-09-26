class Rva7F990ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_0007f990@@YAXXZ
unsigned int *Rva7F990ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
