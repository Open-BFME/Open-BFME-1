struct RvaCB120IdentityWithArgumentThunk
{
    RvaCB120IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cb120@@YAXXZ
RvaCB120IdentityWithArgumentThunk *RvaCB120IdentityWithArgumentThunk::identity(int)
{
    return this;
}
