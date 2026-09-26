struct RvaCB0D0IdentityWithArgumentThunk
{
    RvaCB0D0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cb0d0@@YAXXZ
RvaCB0D0IdentityWithArgumentThunk *RvaCB0D0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
