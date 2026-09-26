struct RvaCAFF0IdentityWithArgumentThunk
{
    RvaCAFF0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000caff0@@YAXXZ
RvaCAFF0IdentityWithArgumentThunk *RvaCAFF0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
