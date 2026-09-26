struct RvaA8C10IdentityWithArgumentThunk
{
    RvaA8C10IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000a8c10@@YAXXZ
RvaA8C10IdentityWithArgumentThunk *RvaA8C10IdentityWithArgumentThunk::identity(int)
{
    return this;
}
