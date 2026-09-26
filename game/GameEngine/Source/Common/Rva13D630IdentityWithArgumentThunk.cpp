struct Rva13D630IdentityWithArgumentThunk
{
    Rva13D630IdentityWithArgumentThunk *identity(int unused);
};

// ?d_0013d630@@YAXXZ
Rva13D630IdentityWithArgumentThunk *Rva13D630IdentityWithArgumentThunk::identity(int)
{
    return this;
}
