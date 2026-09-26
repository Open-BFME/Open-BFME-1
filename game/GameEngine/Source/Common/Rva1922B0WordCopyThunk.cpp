struct Rva1922B0WordCopyThunk
{
    unsigned int value;

    Rva1922B0WordCopyThunk *copy(const Rva1922B0WordCopyThunk *other);
};

// ?d_001922b0@@YAXXZ
Rva1922B0WordCopyThunk *Rva1922B0WordCopyThunk::copy(const Rva1922B0WordCopyThunk *other)
{
    value = other->value;
    return this;
}
