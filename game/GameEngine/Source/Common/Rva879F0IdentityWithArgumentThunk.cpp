struct Rva879F0IdentityWithArgumentThunk
{
    Rva879F0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000879f0@@YAXXZ
Rva879F0IdentityWithArgumentThunk *Rva879F0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
