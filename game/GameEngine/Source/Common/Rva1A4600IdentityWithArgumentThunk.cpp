struct Rva1A4600IdentityWithArgumentThunk
{
    Rva1A4600IdentityWithArgumentThunk *identity(int unused);
};

// ?d_001a4600@@YAXXZ
Rva1A4600IdentityWithArgumentThunk *Rva1A4600IdentityWithArgumentThunk::identity(int)
{
    return this;
}
