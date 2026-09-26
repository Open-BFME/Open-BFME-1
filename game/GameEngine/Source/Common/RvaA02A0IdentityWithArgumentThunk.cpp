struct RvaA02A0IdentityWithArgumentThunk
{
    RvaA02A0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000a02a0@@YAXXZ
RvaA02A0IdentityWithArgumentThunk *RvaA02A0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
