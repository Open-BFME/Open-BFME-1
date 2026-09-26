class Rva13E680ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_0013e680@@YAXXZ
unsigned int *Rva13E680ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
