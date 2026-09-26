struct Rva133280IdentityWithArgumentThunk
{
    Rva133280IdentityWithArgumentThunk *identity(int unused);
};

// ?d_00133280@@YAXXZ
Rva133280IdentityWithArgumentThunk *Rva133280IdentityWithArgumentThunk::identity(int)
{
    return this;
}
