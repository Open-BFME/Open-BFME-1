struct RvaE59F0IdentityWithArgumentThunk
{
    RvaE59F0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000e59f0@@YAXXZ
RvaE59F0IdentityWithArgumentThunk *RvaE59F0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
