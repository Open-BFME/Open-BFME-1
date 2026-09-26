struct RvaED070IdentityWithArgumentThunk
{
    RvaED070IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000ed070@@YAXXZ
RvaED070IdentityWithArgumentThunk *RvaED070IdentityWithArgumentThunk::identity(int)
{
    return this;
}
