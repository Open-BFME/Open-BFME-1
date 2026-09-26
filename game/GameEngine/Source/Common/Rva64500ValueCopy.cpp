class Rva64500ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_00064500@@YAXXZ
unsigned int *Rva64500ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
