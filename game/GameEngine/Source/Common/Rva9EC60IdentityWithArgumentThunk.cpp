struct Rva9EC60IdentityWithArgumentThunk
{
    Rva9EC60IdentityWithArgumentThunk *identity(int unused);
};

// ?d_0009ec60@@YAXXZ
Rva9EC60IdentityWithArgumentThunk *Rva9EC60IdentityWithArgumentThunk::identity(int)
{
    return this;
}
