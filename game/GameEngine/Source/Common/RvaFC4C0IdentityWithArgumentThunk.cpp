struct RvaFC4C0IdentityWithArgumentThunk
{
    RvaFC4C0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000fc4c0@@YAXXZ
RvaFC4C0IdentityWithArgumentThunk *RvaFC4C0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
