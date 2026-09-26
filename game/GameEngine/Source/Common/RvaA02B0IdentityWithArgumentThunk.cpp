struct RvaA02B0IdentityWithArgumentThunk
{
    RvaA02B0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000a02b0@@YAXXZ
RvaA02B0IdentityWithArgumentThunk *RvaA02B0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
