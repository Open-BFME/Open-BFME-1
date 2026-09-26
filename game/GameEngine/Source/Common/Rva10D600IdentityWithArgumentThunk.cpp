struct Rva10D600IdentityWithArgumentThunk
{
    Rva10D600IdentityWithArgumentThunk *identity(int unused);
};

// ?d_0010d600@@YAXXZ
Rva10D600IdentityWithArgumentThunk *Rva10D600IdentityWithArgumentThunk::identity(int)
{
    return this;
}
