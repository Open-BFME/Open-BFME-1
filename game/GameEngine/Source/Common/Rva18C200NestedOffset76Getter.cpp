struct Rva18C200NestedValue
{
    unsigned char unused[76];
    unsigned int value;
};

struct Rva18C200NestedOffset76Getter
{
    unsigned char unused[8];
    Rva18C200NestedValue *nested;

    unsigned int get_value();
};

// ?d_0018c200@@YAXXZ
unsigned int Rva18C200NestedOffset76Getter::get_value()
{
    return nested->value;
}
