class Rva13E660ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_0013e660@@YAXXZ
unsigned int *Rva13E660ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
