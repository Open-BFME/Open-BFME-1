struct Rva92A00IdentityWithArgumentThunk
{
    Rva92A00IdentityWithArgumentThunk *identity(int unused);
};

// ?d_00092a00@@YAXXZ
Rva92A00IdentityWithArgumentThunk *Rva92A00IdentityWithArgumentThunk::identity(int)
{
    return this;
}
