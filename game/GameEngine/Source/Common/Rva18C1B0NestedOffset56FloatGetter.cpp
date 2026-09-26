struct Rva18C1B0NestedFloat
{
    unsigned char unused[56];
    float value;
};

struct Rva18C1B0NestedOffset56FloatGetter
{
    unsigned char unused[8];
    Rva18C1B0NestedFloat *nested;

    float get_value();
};

// ?d_0018c1b0@@YAXXZ
float Rva18C1B0NestedOffset56FloatGetter::get_value()
{
    return nested->value;
}
