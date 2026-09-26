struct StoredEightByteHeaderPointerThunk
{
    unsigned char *pointer;

    unsigned char *payload() const;
};

// ?d_00061b90@@YAXXZ
unsigned char *StoredEightByteHeaderPointerThunk::payload() const
{
    return pointer + 8;
}
