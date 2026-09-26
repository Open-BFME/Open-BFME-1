struct Rva122A90IdentityWithArgumentThunk
{
    Rva122A90IdentityWithArgumentThunk *identity(int unused);
};

// ?d_00122a90@@YAXXZ
Rva122A90IdentityWithArgumentThunk *Rva122A90IdentityWithArgumentThunk::identity(int)
{
    return this;
}
