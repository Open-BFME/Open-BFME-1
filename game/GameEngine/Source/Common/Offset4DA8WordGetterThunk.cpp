struct Offset4DA8WordGetterThunk
{
    unsigned char padding[0x4DA8];
    unsigned long value;

    unsigned long getValue() const;
};

// ?d_0005c460@@YAXXZ
unsigned long Offset4DA8WordGetterThunk::getValue() const
{
    return value;
}
