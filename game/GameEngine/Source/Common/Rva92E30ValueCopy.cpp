class Rva92E30ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_00092e30@@YAXXZ
unsigned int *Rva92E30ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
