struct Rva18C1A0NestedFloat
{
    unsigned char unused[48];
    float value;
};

struct Rva18C1A0NestedOffset48FloatGetter
{
    unsigned char unused[8];
    Rva18C1A0NestedFloat *nested;

    float get_value();
};

// ?d_0018c1a0@@YAXXZ
float Rva18C1A0NestedOffset48FloatGetter::get_value()
{
    return nested->value;
}
