struct Rva1229D0IdentityWithArgumentThunk
{
    Rva1229D0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_001229d0@@YAXXZ
Rva1229D0IdentityWithArgumentThunk *Rva1229D0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
