struct Rva9EC90StoredPointerOffsetThunk
{
    char *value;

    char *offsetValue() const;
};

// ?d_0009ec90@@YAXXZ
char *Rva9EC90StoredPointerOffsetThunk::offsetValue() const
{
    return value + 8;
}
