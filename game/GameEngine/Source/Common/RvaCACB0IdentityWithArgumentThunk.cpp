struct RvaCACB0IdentityWithArgumentThunk
{
    RvaCACB0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cacb0@@YAXXZ
RvaCACB0IdentityWithArgumentThunk *RvaCACB0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
