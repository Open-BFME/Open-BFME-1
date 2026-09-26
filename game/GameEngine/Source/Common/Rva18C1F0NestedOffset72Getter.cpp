struct Rva18C1F0NestedValue
{
    unsigned char unused[72];
    unsigned int value;
};

struct Rva18C1F0NestedOffset72Getter
{
    unsigned char unused[8];
    Rva18C1F0NestedValue *nested;

    unsigned int get_value();
};

// ?d_0018c1f0@@YAXXZ
unsigned int Rva18C1F0NestedOffset72Getter::get_value()
{
    return nested->value;
}
