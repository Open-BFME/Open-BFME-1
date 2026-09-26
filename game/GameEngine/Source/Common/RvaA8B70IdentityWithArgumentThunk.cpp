struct RvaA8B70IdentityWithArgumentThunk
{
    RvaA8B70IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000a8b70@@YAXXZ
RvaA8B70IdentityWithArgumentThunk *RvaA8B70IdentityWithArgumentThunk::identity(int)
{
    return this;
}
