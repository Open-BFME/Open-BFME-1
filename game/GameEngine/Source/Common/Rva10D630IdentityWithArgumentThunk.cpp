struct Rva10D630IdentityWithArgumentThunk
{
    Rva10D630IdentityWithArgumentThunk *identity(int unused);
};

// ?d_0010d630@@YAXXZ
Rva10D630IdentityWithArgumentThunk *Rva10D630IdentityWithArgumentThunk::identity(int)
{
    return this;
}
