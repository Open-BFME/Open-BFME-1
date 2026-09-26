struct Rva87AD0IdentityWithArgumentThunk
{
    Rva87AD0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_00087ad0@@YAXXZ
Rva87AD0IdentityWithArgumentThunk *Rva87AD0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
