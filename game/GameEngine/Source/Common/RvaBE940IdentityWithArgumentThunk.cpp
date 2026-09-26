struct RvaBE940IdentityWithArgumentThunk
{
    RvaBE940IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000be940@@YAXXZ
RvaBE940IdentityWithArgumentThunk *RvaBE940IdentityWithArgumentThunk::identity(int)
{
    return this;
}
