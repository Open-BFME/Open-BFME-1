struct RvaE0D50IdentityWithArgumentThunk
{
    RvaE0D50IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000e0d50@@YAXXZ
RvaE0D50IdentityWithArgumentThunk *RvaE0D50IdentityWithArgumentThunk::identity(int)
{
    return this;
}
