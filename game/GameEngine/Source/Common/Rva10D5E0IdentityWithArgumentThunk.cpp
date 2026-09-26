struct Rva10D5E0IdentityWithArgumentThunk
{
    Rva10D5E0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_0010d5e0@@YAXXZ
Rva10D5E0IdentityWithArgumentThunk *Rva10D5E0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
