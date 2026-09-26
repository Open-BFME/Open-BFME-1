class RvaBF010ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_000bf010@@YAXXZ
unsigned int *RvaBF010ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
