struct RvaCB160IdentityWithArgumentThunk
{
    RvaCB160IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cb160@@YAXXZ
RvaCB160IdentityWithArgumentThunk *RvaCB160IdentityWithArgumentThunk::identity(int)
{
    return this;
}
