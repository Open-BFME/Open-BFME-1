struct Offset5E24ByteSetterThunk
{
    unsigned char padding[0x5E24];
    unsigned char value;

    void setValue(unsigned char newValue);
};

// ?d_0005c470@@YAXXZ
void Offset5E24ByteSetterThunk::setValue(unsigned char newValue)
{
    value = newValue;
}
