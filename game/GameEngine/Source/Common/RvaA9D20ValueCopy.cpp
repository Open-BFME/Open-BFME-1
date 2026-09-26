class RvaA9D20ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_000a9d20@@YAXXZ
unsigned int *RvaA9D20ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
