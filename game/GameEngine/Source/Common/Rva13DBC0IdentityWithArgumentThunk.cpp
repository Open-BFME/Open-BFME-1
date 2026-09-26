struct Rva13DBC0IdentityWithArgumentThunk
{
    Rva13DBC0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_0013dbc0@@YAXXZ
Rva13DBC0IdentityWithArgumentThunk *Rva13DBC0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
