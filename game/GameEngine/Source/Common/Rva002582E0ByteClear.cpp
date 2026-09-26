class Rva002582E0ByteClear
{
    char padding[0x14];
    unsigned char value;

public:
    void clear();
};

void Rva002582E0ByteClear::clear()
{
    value = 0;
}
