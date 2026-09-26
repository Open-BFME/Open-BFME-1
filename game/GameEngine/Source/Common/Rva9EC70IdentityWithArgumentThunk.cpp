struct Rva9EC70IdentityWithArgumentThunk
{
    Rva9EC70IdentityWithArgumentThunk *identity(int unused);
};

// ?d_0009ec70@@YAXXZ
Rva9EC70IdentityWithArgumentThunk *Rva9EC70IdentityWithArgumentThunk::identity(int)
{
    return this;
}
