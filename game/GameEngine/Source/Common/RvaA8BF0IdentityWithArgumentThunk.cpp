struct RvaA8BF0IdentityWithArgumentThunk
{
    RvaA8BF0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000a8bf0@@YAXXZ
RvaA8BF0IdentityWithArgumentThunk *RvaA8BF0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
