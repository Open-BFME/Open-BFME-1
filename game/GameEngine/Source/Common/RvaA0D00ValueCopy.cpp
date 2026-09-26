class RvaA0D00ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_000a0d00@@YAXXZ
unsigned int *RvaA0D00ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
