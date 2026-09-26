class Rva124CF0ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_00124cf0@@YAXXZ
unsigned int *Rva124CF0ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
