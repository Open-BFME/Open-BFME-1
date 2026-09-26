struct Rva133270IdentityWithArgumentThunk
{
    Rva133270IdentityWithArgumentThunk *identity(int unused);
};

// ?d_00133270@@YAXXZ
Rva133270IdentityWithArgumentThunk *Rva133270IdentityWithArgumentThunk::identity(int)
{
    return this;
}
