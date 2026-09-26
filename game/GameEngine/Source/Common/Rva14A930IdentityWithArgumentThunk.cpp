struct Rva14A930IdentityWithArgumentThunk
{
    Rva14A930IdentityWithArgumentThunk *identity(int unused);
};

// ?d_0014a930@@YAXXZ
Rva14A930IdentityWithArgumentThunk *Rva14A930IdentityWithArgumentThunk::identity(int)
{
    return this;
}
