struct RvaCB0C0IdentityWithArgumentThunk
{
    RvaCB0C0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cb0c0@@YAXXZ
RvaCB0C0IdentityWithArgumentThunk *RvaCB0C0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
