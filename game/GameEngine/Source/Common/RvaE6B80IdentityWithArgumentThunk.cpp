struct RvaE6B80IdentityWithArgumentThunk
{
    RvaE6B80IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000e6b80@@YAXXZ
RvaE6B80IdentityWithArgumentThunk *RvaE6B80IdentityWithArgumentThunk::identity(int)
{
    return this;
}
