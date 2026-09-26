struct Rva18C180NestedFloat
{
    unsigned char unused[8];
    float value;
};

struct Rva18C180NestedOffset8FloatGetter
{
    unsigned char unused[8];
    Rva18C180NestedFloat *nested;

    float get_value();
};

// ?d_0018c180@@YAXXZ
float Rva18C180NestedOffset8FloatGetter::get_value()
{
    return nested->value;
}
