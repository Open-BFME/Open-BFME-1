class RvaE9060ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_000e9060@@YAXXZ
unsigned int *RvaE9060ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
