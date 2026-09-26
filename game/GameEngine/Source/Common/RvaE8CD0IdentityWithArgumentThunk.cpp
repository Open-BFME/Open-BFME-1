struct RvaE8CD0IdentityWithArgumentThunk
{
    RvaE8CD0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000e8cd0@@YAXXZ
RvaE8CD0IdentityWithArgumentThunk *RvaE8CD0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
