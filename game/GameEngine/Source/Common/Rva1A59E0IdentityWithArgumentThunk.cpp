struct Rva1A59E0IdentityWithArgumentThunk
{
    Rva1A59E0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_001a59e0@@YAXXZ
Rva1A59E0IdentityWithArgumentThunk *Rva1A59E0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
