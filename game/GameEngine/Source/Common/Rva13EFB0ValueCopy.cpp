class Rva13EFB0ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_0013efb0@@YAXXZ
unsigned int *Rva13EFB0ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
