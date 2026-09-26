struct RvaA8C00IdentityWithArgumentThunk
{
    RvaA8C00IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000a8c00@@YAXXZ
RvaA8C00IdentityWithArgumentThunk *RvaA8C00IdentityWithArgumentThunk::identity(int)
{
    return this;
}
