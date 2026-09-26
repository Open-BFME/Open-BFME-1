struct Rva10D5D0IdentityWithArgumentThunk
{
    Rva10D5D0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_0010d5d0@@YAXXZ
Rva10D5D0IdentityWithArgumentThunk *Rva10D5D0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
