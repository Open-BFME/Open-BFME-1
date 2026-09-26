struct Rva92A40IdentityWithArgumentThunk
{
    Rva92A40IdentityWithArgumentThunk *identity(int unused);
};

// ?d_00092a40@@YAXXZ
Rva92A40IdentityWithArgumentThunk *Rva92A40IdentityWithArgumentThunk::identity(int)
{
    return this;
}
