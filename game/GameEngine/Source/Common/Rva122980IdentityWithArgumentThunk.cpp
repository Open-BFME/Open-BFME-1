struct Rva122980IdentityWithArgumentThunk
{
    Rva122980IdentityWithArgumentThunk *identity(int unused);
};

// ?d_00122980@@YAXXZ
Rva122980IdentityWithArgumentThunk *Rva122980IdentityWithArgumentThunk::identity(int)
{
    return this;
}
