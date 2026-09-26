class RvaCEA80ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_000cea80@@YAXXZ
unsigned int *RvaCEA80ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
