class Rva87850ValueReset
{
public:
    unsigned int *reset();

private:
    unsigned int value;
};

// ?d_00087850@@YAXXZ
unsigned int *Rva87850ValueReset::reset()
{
    value = 0;
    return &value;
}
