struct RvaFC4A0IdentityWithArgumentThunk
{
    RvaFC4A0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000fc4a0@@YAXXZ
RvaFC4A0IdentityWithArgumentThunk *RvaFC4A0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
