struct RvaFC4F0IdentityWithArgumentThunk
{
    RvaFC4F0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000fc4f0@@YAXXZ
RvaFC4F0IdentityWithArgumentThunk *RvaFC4F0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
