struct RvaFC4D0IdentityWithArgumentThunk
{
    RvaFC4D0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000fc4d0@@YAXXZ
RvaFC4D0IdentityWithArgumentThunk *RvaFC4D0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
