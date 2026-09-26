class Rva192F10ValueOwner
{
public:
    unsigned int *copy_value(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_00192f10@@YAXXZ
unsigned int *Rva192F10ValueOwner::copy_value(unsigned int *output)
{
    *output = m_value;
    return output;
}
