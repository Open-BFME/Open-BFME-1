class RvaCEA70ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_000cea70@@YAXXZ
unsigned int *RvaCEA70ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
