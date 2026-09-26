struct Rva18C210NestedValue
{
    unsigned char unused[80];
    unsigned int value;
};

struct Rva18C210NestedOffset80Getter
{
    unsigned char unused[8];
    Rva18C210NestedValue *nested;

    unsigned int get_value();
};

// ?d_0018c210@@YAXXZ
unsigned int Rva18C210NestedOffset80Getter::get_value()
{
    return nested->value;
}
