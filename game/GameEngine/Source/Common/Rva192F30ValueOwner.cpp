class Rva192F30ValueOwner
{
public:
    unsigned int *copy_value(unsigned int *output);

private:
    unsigned int m_value;
};

// ?d_00192f30@@YAXXZ
unsigned int *Rva192F30ValueOwner::copy_value(unsigned int *output)
{
    *output = m_value;
    return output;
}
