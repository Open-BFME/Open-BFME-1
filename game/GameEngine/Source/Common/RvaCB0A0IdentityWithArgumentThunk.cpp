struct RvaCB0A0IdentityWithArgumentThunk
{
    RvaCB0A0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cb0a0@@YAXXZ
RvaCB0A0IdentityWithArgumentThunk *RvaCB0A0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
