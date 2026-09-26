class Rva87710ValueReset
{
public:
    unsigned int *reset();

private:
    unsigned int value;
};

// ?d_00087710@@YAXXZ
unsigned int *Rva87710ValueReset::reset()
{
    value = 0;
    return &value;
}
