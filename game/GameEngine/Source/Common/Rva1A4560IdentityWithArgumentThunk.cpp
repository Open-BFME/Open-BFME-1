struct Rva1A4560IdentityWithArgumentThunk
{
    Rva1A4560IdentityWithArgumentThunk *identity(int unused);
};

// ?d_001a4560@@YAXXZ
Rva1A4560IdentityWithArgumentThunk *Rva1A4560IdentityWithArgumentThunk::identity(int)
{
    return this;
}
