class RvaCC980ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_000cc980@@YAXXZ
unsigned int *RvaCC980ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
