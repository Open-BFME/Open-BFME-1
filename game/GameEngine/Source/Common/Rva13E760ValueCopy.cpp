class Rva13E760ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_0013e760@@YAXXZ
unsigned int *Rva13E760ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
