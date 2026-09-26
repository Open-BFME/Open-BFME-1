struct Rva18C120NestedValue
{
    unsigned char unused[0x44];
    unsigned int value;
};

struct Rva18C120NestedOffset44Getter
{
    unsigned char unused[0x1C];
    Rva18C120NestedValue *nested;

    unsigned int get_value();
};

// ?d_0018c120@@YAXXZ
unsigned int Rva18C120NestedOffset44Getter::get_value()
{
    return nested->value;
}
