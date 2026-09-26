class RvaA0900ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_000a0900@@YAXXZ
unsigned int *RvaA0900ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
