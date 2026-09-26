struct Rva191F90IdentityWithArgumentThunk
{
    Rva191F90IdentityWithArgumentThunk *identity(int unused);
};

// ?d_00191f90@@YAXXZ
Rva191F90IdentityWithArgumentThunk *Rva191F90IdentityWithArgumentThunk::identity(int)
{
    return this;
}
