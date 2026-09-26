struct RvaF9410IdentityWithArgumentThunk
{
    RvaF9410IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000f9410@@YAXXZ
RvaF9410IdentityWithArgumentThunk *RvaF9410IdentityWithArgumentThunk::identity(int)
{
    return this;
}
