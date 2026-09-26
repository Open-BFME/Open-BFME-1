class Rva8E430ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_0008e430@@YAXXZ
unsigned int *Rva8E430ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
