class Rva13E830ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_0013e830@@YAXXZ
unsigned int *Rva13E830ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
