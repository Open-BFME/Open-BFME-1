struct Rva122960IdentityWithArgumentThunk
{
    Rva122960IdentityWithArgumentThunk *identity(int unused);
};

// ?d_00122960@@YAXXZ
Rva122960IdentityWithArgumentThunk *Rva122960IdentityWithArgumentThunk::identity(int)
{
    return this;
}
