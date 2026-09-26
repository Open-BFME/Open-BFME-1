class RvaCC4F0ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_000cc4f0@@YAXXZ
unsigned int *RvaCC4F0ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
