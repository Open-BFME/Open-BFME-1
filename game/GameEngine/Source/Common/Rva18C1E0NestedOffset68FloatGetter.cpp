struct Rva18C1E0NestedFloat
{
    unsigned char unused[68];
    float value;
};

struct Rva18C1E0NestedOffset68FloatGetter
{
    unsigned char unused[8];
    Rva18C1E0NestedFloat *nested;

    float get_value();
};

// ?d_0018c1e0@@YAXXZ
float Rva18C1E0NestedOffset68FloatGetter::get_value()
{
    return nested->value;
}
