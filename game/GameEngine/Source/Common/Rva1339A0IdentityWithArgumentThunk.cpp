struct Rva1339A0IdentityWithArgumentThunk
{
    Rva1339A0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_001339a0@@YAXXZ
Rva1339A0IdentityWithArgumentThunk *Rva1339A0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
