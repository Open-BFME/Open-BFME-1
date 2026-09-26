struct RvaBE8E0IdentityWithArgumentThunk
{
    RvaBE8E0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000be8e0@@YAXXZ
RvaBE8E0IdentityWithArgumentThunk *RvaBE8E0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
