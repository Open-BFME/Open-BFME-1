struct Rva97E10IdentityWithArgumentThunk
{
    Rva97E10IdentityWithArgumentThunk *identity(int unused);
};

// ?d_00097e10@@YAXXZ
Rva97E10IdentityWithArgumentThunk *Rva97E10IdentityWithArgumentThunk::identity(int)
{
    return this;
}
