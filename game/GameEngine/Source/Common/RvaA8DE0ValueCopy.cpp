class RvaA8DE0ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_000a8de0@@YAXXZ
unsigned int *RvaA8DE0ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
