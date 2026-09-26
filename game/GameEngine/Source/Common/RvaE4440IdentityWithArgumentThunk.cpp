struct RvaE4440IdentityWithArgumentThunk
{
    RvaE4440IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000e4440@@YAXXZ
RvaE4440IdentityWithArgumentThunk *RvaE4440IdentityWithArgumentThunk::identity(int)
{
    return this;
}
