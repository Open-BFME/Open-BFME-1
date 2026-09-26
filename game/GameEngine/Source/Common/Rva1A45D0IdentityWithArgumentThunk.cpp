struct Rva1A45D0IdentityWithArgumentThunk
{
    Rva1A45D0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_001a45d0@@YAXXZ
Rva1A45D0IdentityWithArgumentThunk *Rva1A45D0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
