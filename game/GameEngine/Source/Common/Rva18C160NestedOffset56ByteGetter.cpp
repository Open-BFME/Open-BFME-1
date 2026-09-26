struct Rva18C160NestedByte
{
    unsigned char unused[0x56];
    unsigned char value;
};

struct Rva18C160NestedOffset56ByteGetter
{
    unsigned char unused[8];
    Rva18C160NestedByte *nested;

    unsigned char get_value();
};

// ?d_0018c160@@YAXXZ
unsigned char Rva18C160NestedOffset56ByteGetter::get_value()
{
    return nested->value;
}
