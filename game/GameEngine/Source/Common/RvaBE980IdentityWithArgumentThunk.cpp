struct RvaBE980IdentityWithArgumentThunk
{
    RvaBE980IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000be980@@YAXXZ
RvaBE980IdentityWithArgumentThunk *RvaBE980IdentityWithArgumentThunk::identity(int)
{
    return this;
}
