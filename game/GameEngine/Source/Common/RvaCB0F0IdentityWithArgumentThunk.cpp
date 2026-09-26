struct RvaCB0F0IdentityWithArgumentThunk
{
    RvaCB0F0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cb0f0@@YAXXZ
RvaCB0F0IdentityWithArgumentThunk *RvaCB0F0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
