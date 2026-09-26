struct Rva1229C0IdentityWithArgumentThunk
{
    Rva1229C0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_001229c0@@YAXXZ
Rva1229C0IdentityWithArgumentThunk *Rva1229C0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
