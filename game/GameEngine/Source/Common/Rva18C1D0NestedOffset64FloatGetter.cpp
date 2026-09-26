struct Rva18C1D0NestedFloat
{
    unsigned char unused[64];
    float value;
};

struct Rva18C1D0NestedOffset64FloatGetter
{
    unsigned char unused[8];
    Rva18C1D0NestedFloat *nested;

    float get_value();
};

// ?d_0018c1d0@@YAXXZ
float Rva18C1D0NestedOffset64FloatGetter::get_value()
{
    return nested->value;
}
