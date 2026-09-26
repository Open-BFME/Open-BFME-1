struct Rva105870Offset16ByteOneSetterThunk
{
    unsigned char unused[16];
    unsigned char enabled;

    void enable();
};

void Rva105870Offset16ByteOneSetterThunk::enable()
{
    enabled = true;
}
