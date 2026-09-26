struct Rva92A50IdentityWithArgumentThunk
{
    Rva92A50IdentityWithArgumentThunk *identity(int unused);
};

// ?d_00092a50@@YAXXZ
Rva92A50IdentityWithArgumentThunk *Rva92A50IdentityWithArgumentThunk::identity(int)
{
    return this;
}
