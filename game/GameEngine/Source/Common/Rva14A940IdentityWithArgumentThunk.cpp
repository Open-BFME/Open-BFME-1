struct Rva14A940IdentityWithArgumentThunk
{
    Rva14A940IdentityWithArgumentThunk *identity(int unused);
};

// ?d_0014a940@@YAXXZ
Rva14A940IdentityWithArgumentThunk *Rva14A940IdentityWithArgumentThunk::identity(int)
{
    return this;
}
