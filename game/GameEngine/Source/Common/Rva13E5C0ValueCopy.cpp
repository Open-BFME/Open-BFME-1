class Rva13E5C0ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_0013e5c0@@YAXXZ
unsigned int *Rva13E5C0ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
