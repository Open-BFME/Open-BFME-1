struct Rva94D10IdentityWithArgumentThunk
{
    Rva94D10IdentityWithArgumentThunk *identity(int unused);
};

// ?d_00094d10@@YAXXZ
Rva94D10IdentityWithArgumentThunk *Rva94D10IdentityWithArgumentThunk::identity(int)
{
    return this;
}
