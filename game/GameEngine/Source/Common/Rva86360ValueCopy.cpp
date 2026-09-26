class Rva86360ValueCopy
{
public:
    unsigned int *copy(unsigned int *source);

private:
    unsigned int value;
};

// ?d_00086360@@YAXXZ
unsigned int *Rva86360ValueCopy::copy(unsigned int *source)
{
    value = *source;
    return &value;
}
