struct RvaEB1B0IdentityWithArgumentThunk
{
    RvaEB1B0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000eb1b0@@YAXXZ
RvaEB1B0IdentityWithArgumentThunk *RvaEB1B0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
