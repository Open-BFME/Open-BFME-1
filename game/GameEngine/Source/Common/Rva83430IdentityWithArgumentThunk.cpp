struct Rva83430IdentityWithArgumentThunk
{
    Rva83430IdentityWithArgumentThunk *identity(int unused);
};

// ?d_00083430@@YAXXZ
Rva83430IdentityWithArgumentThunk *Rva83430IdentityWithArgumentThunk::identity(int)
{
    return this;
}
