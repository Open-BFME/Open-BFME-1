struct Rva122970IdentityWithArgumentThunk
{
    Rva122970IdentityWithArgumentThunk *identity(int unused);
};

// ?d_00122970@@YAXXZ
Rva122970IdentityWithArgumentThunk *Rva122970IdentityWithArgumentThunk::identity(int)
{
    return this;
}
