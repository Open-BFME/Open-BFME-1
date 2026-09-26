struct Rva10D620IdentityWithArgumentThunk
{
    Rva10D620IdentityWithArgumentThunk *identity(int unused);
};

// ?d_0010d620@@YAXXZ
Rva10D620IdentityWithArgumentThunk *Rva10D620IdentityWithArgumentThunk::identity(int)
{
    return this;
}
