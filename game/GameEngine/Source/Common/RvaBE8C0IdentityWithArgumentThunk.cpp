struct RvaBE8C0IdentityWithArgumentThunk
{
    RvaBE8C0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000be8c0@@YAXXZ
RvaBE8C0IdentityWithArgumentThunk *RvaBE8C0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
