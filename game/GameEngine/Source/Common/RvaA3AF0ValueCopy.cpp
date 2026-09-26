class RvaA3AF0ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_000a3af0@@YAXXZ
unsigned int *RvaA3AF0ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
