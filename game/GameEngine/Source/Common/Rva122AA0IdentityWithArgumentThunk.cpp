struct Rva122AA0IdentityWithArgumentThunk
{
    Rva122AA0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_00122aa0@@YAXXZ
Rva122AA0IdentityWithArgumentThunk *Rva122AA0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
