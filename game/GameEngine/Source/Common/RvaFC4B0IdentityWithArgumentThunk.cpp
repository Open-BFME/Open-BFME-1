struct RvaFC4B0IdentityWithArgumentThunk
{
    RvaFC4B0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000fc4b0@@YAXXZ
RvaFC4B0IdentityWithArgumentThunk *RvaFC4B0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
