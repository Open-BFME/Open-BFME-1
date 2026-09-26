struct RvaCB150IdentityWithArgumentThunk
{
    RvaCB150IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cb150@@YAXXZ
RvaCB150IdentityWithArgumentThunk *RvaCB150IdentityWithArgumentThunk::identity(int)
{
    return this;
}
