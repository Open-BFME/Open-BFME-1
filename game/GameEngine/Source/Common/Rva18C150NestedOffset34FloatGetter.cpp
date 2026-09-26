struct Rva18C150NestedFloat
{
    unsigned char unused[0x34];
    float value;
};

struct Rva18C150NestedOffset34FloatGetter
{
    unsigned char unused[8];
    Rva18C150NestedFloat *nested;

    float get_value();
};

// ?d_0018c150@@YAXXZ
float Rva18C150NestedOffset34FloatGetter::get_value()
{
    return nested->value;
}
