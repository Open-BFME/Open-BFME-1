struct Rva14A970IdentityWithArgumentThunk
{
    Rva14A970IdentityWithArgumentThunk *identity(int unused);
};

// ?d_0014a970@@YAXXZ
Rva14A970IdentityWithArgumentThunk *Rva14A970IdentityWithArgumentThunk::identity(int)
{
    return this;
}
