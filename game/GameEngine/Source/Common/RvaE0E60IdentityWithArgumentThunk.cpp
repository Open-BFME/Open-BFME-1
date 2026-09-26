struct RvaE0E60IdentityWithArgumentThunk
{
    RvaE0E60IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000e0e60@@YAXXZ
RvaE0E60IdentityWithArgumentThunk *RvaE0E60IdentityWithArgumentThunk::identity(int)
{
    return this;
}
