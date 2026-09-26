class RvaE16E0ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_000e16e0@@YAXXZ
unsigned int *RvaE16E0ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
