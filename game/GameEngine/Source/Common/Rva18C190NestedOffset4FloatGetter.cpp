struct Rva18C190NestedFloat
{
    unsigned char unused[4];
    float value;
};

struct Rva18C190NestedOffset4FloatGetter
{
    unsigned char unused[8];
    Rva18C190NestedFloat *nested;

    float get_value();
};

// ?d_0018c190@@YAXXZ
float Rva18C190NestedOffset4FloatGetter::get_value()
{
    return nested->value;
}
