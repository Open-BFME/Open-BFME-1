class Rva13E800ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_0013e800@@YAXXZ
unsigned int *Rva13E800ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
