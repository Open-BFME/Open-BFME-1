struct Rva122990IdentityWithArgumentThunk
{
    Rva122990IdentityWithArgumentThunk *identity(int unused);
};

// ?d_00122990@@YAXXZ
Rva122990IdentityWithArgumentThunk *Rva122990IdentityWithArgumentThunk::identity(int)
{
    return this;
}
