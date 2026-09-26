class Rva13EFA0ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_0013efa0@@YAXXZ
unsigned int *Rva13EFA0ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
