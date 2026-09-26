struct Rva18C170NestedFloat
{
    float value;
};

struct Rva18C170NestedFloatGetter
{
    unsigned char unused[8];
    Rva18C170NestedFloat *nested;

    float get_value();
};

// ?d_0018c170@@YAXXZ
float Rva18C170NestedFloatGetter::get_value()
{
    return nested->value;
}
