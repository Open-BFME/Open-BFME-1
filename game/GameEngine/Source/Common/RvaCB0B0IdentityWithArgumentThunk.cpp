struct RvaCB0B0IdentityWithArgumentThunk
{
    RvaCB0B0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cb0b0@@YAXXZ
RvaCB0B0IdentityWithArgumentThunk *RvaCB0B0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
