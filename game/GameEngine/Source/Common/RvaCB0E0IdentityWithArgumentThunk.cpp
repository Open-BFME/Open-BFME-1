struct RvaCB0E0IdentityWithArgumentThunk
{
    RvaCB0E0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cb0e0@@YAXXZ
RvaCB0E0IdentityWithArgumentThunk *RvaCB0E0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
