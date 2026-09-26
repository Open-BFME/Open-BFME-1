struct Rva191F40IdentityWithArgumentThunk
{
    Rva191F40IdentityWithArgumentThunk *identity(int unused);
};

// ?d_00191f40@@YAXXZ
Rva191F40IdentityWithArgumentThunk *Rva191F40IdentityWithArgumentThunk::identity(int)
{
    return this;
}
