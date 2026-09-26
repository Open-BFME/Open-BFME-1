struct RvaE0E70IdentityWithArgumentThunk
{
    RvaE0E70IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000e0e70@@YAXXZ
RvaE0E70IdentityWithArgumentThunk *RvaE0E70IdentityWithArgumentThunk::identity(int)
{
    return this;
}
