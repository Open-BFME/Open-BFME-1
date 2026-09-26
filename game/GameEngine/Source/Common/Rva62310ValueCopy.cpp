class Rva62310ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_00062310@@YAXXZ
unsigned int *Rva62310ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
