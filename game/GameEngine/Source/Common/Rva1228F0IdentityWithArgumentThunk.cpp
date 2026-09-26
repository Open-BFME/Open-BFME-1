struct Rva1228F0IdentityWithArgumentThunk
{
    Rva1228F0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_001228f0@@YAXXZ
Rva1228F0IdentityWithArgumentThunk *Rva1228F0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
