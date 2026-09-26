class Rva192F00ValueOwner
{
public:
    unsigned int *copy_value(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_00192f00@@YAXXZ
unsigned int *Rva192F00ValueOwner::copy_value(unsigned int *output)
{
    *output = m_value;
    return output;
}
