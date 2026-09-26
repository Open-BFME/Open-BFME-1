struct RvaE6AB0IdentityWithArgumentThunk
{
    RvaE6AB0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000e6ab0@@YAXXZ
RvaE6AB0IdentityWithArgumentThunk *RvaE6AB0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
