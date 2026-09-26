struct Rva122950IdentityWithArgumentThunk
{
    Rva122950IdentityWithArgumentThunk *identity(int unused);
};

// ?d_00122950@@YAXXZ
Rva122950IdentityWithArgumentThunk *Rva122950IdentityWithArgumentThunk::identity(int)
{
    return this;
}
