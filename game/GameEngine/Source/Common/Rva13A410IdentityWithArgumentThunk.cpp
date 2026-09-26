struct Rva13A410IdentityWithArgumentThunk
{
    Rva13A410IdentityWithArgumentThunk *identity(int unused);
};

// ?d_0013a410@@YAXXZ
Rva13A410IdentityWithArgumentThunk *Rva13A410IdentityWithArgumentThunk::identity(int)
{
    return this;
}
