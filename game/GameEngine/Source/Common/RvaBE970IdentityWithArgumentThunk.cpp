struct RvaBE970IdentityWithArgumentThunk
{
    RvaBE970IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000be970@@YAXXZ
RvaBE970IdentityWithArgumentThunk *RvaBE970IdentityWithArgumentThunk::identity(int)
{
    return this;
}
