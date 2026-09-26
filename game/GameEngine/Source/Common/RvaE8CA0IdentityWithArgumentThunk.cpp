struct RvaE8CA0IdentityWithArgumentThunk
{
    RvaE8CA0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000e8ca0@@YAXXZ
RvaE8CA0IdentityWithArgumentThunk *RvaE8CA0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
