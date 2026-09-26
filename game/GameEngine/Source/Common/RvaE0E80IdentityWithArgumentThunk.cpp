struct RvaE0E80IdentityWithArgumentThunk
{
    RvaE0E80IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000e0e80@@YAXXZ
RvaE0E80IdentityWithArgumentThunk *RvaE0E80IdentityWithArgumentThunk::identity(int)
{
    return this;
}
