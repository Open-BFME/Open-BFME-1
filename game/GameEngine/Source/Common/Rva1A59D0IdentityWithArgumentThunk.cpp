struct Rva1A59D0IdentityWithArgumentThunk
{
    Rva1A59D0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_001a59d0@@YAXXZ
Rva1A59D0IdentityWithArgumentThunk *Rva1A59D0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
