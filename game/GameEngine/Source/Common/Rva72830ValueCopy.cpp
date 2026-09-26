class Rva72830ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_00072830@@YAXXZ
unsigned int *Rva72830ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
