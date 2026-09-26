class RvaFCAF0ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_000fcaf0@@YAXXZ
unsigned int *RvaFCAF0ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
