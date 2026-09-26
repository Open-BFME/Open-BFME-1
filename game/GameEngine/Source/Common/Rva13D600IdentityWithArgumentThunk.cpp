struct Rva13D600IdentityWithArgumentThunk
{
    Rva13D600IdentityWithArgumentThunk *identity(int unused);
};

// ?d_0013d600@@YAXXZ
Rva13D600IdentityWithArgumentThunk *Rva13D600IdentityWithArgumentThunk::identity(int)
{
    return this;
}
