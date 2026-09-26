struct Rva18C1C0NestedFloat
{
    unsigned char unused[12];
    float value;
};

struct Rva18C1C0NestedOffset12FloatGetter
{
    unsigned char unused[8];
    Rva18C1C0NestedFloat *nested;

    float get_value();
};

// ?d_0018c1c0@@YAXXZ
float Rva18C1C0NestedOffset12FloatGetter::get_value()
{
    return nested->value;
}
