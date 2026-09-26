struct RvaE59E0IdentityWithArgumentThunk
{
    RvaE59E0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000e59e0@@YAXXZ
RvaE59E0IdentityWithArgumentThunk *RvaE59E0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
