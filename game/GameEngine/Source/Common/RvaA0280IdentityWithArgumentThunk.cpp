struct RvaA0280IdentityWithArgumentThunk
{
    RvaA0280IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000a0280@@YAXXZ
RvaA0280IdentityWithArgumentThunk *RvaA0280IdentityWithArgumentThunk::identity(int)
{
    return this;
}
