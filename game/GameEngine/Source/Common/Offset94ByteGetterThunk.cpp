struct Offset94ByteGetterThunk
{
    unsigned char padding[0x94];
    unsigned char value;

    unsigned char getValue() const;
};

unsigned char Offset94ByteGetterThunk::getValue() const
{
    return value;
}
