struct RvaBE950IdentityWithArgumentThunk
{
    RvaBE950IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000be950@@YAXXZ
RvaBE950IdentityWithArgumentThunk *RvaBE950IdentityWithArgumentThunk::identity(int)
{
    return this;
}
