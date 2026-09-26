struct Rva1A4570IdentityWithArgumentThunk
{
    Rva1A4570IdentityWithArgumentThunk *identity(int unused);
};

// ?d_001a4570@@YAXXZ
Rva1A4570IdentityWithArgumentThunk *Rva1A4570IdentityWithArgumentThunk::identity(int)
{
    return this;
}
