struct StoredFourByteHeaderPointerThunk
{
    unsigned char *pointer;

    unsigned char *payload() const;
};

// ?d_00061d40@@YAXXZ
unsigned char *StoredFourByteHeaderPointerThunk::payload() const
{
    return pointer + 4;
}
