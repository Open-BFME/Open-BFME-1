struct RvaCADB0IdentityWithArgumentThunk
{
    RvaCADB0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cadb0@@YAXXZ
RvaCADB0IdentityWithArgumentThunk *RvaCADB0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
