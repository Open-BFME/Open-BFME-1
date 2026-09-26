struct Rva14A960IdentityWithArgumentThunk
{
    Rva14A960IdentityWithArgumentThunk *identity(int unused);
};

// ?d_0014a960@@YAXXZ
Rva14A960IdentityWithArgumentThunk *Rva14A960IdentityWithArgumentThunk::identity(int)
{
    return this;
}
