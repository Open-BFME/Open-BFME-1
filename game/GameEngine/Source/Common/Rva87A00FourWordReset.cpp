class Rva87A00FourWordReset
{
public:
    unsigned int *reset();

private:
    unsigned int value0;
    unsigned int value4;
    unsigned int value8;
    unsigned int valueC;
};

unsigned int *Rva87A00FourWordReset::reset()
{
    value0 = 0;
    value4 = 0;
    value8 = 0;
    valueC = 0;
    return &value0;
}
