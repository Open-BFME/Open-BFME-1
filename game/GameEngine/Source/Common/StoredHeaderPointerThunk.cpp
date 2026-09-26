struct StoredHeaderPointerThunk
{
    unsigned char *pointer;

    unsigned char *payload() const;
};

// ?d_00061610@@YAXXZ
unsigned char *StoredHeaderPointerThunk::payload() const
{
    return pointer + 12;
}
