struct Rva10D5C0IdentityWithArgumentThunk
{
    Rva10D5C0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_0010d5c0@@YAXXZ
Rva10D5C0IdentityWithArgumentThunk *Rva10D5C0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
