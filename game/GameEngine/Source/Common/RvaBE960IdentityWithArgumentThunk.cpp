struct RvaBE960IdentityWithArgumentThunk
{
    RvaBE960IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000be960@@YAXXZ
RvaBE960IdentityWithArgumentThunk *RvaBE960IdentityWithArgumentThunk::identity(int)
{
    return this;
}
