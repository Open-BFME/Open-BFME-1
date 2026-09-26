struct Rva1331C0IdentityWithArgumentThunk
{
    Rva1331C0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_001331c0@@YAXXZ
Rva1331C0IdentityWithArgumentThunk *Rva1331C0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
