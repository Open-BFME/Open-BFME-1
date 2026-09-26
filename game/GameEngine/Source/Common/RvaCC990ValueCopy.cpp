class RvaCC990ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_000cc990@@YAXXZ
unsigned int *RvaCC990ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
