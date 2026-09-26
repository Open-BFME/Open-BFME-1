struct RvaCB090IdentityWithArgumentThunk
{
    RvaCB090IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cb090@@YAXXZ
RvaCB090IdentityWithArgumentThunk *RvaCB090IdentityWithArgumentThunk::identity(int)
{
    return this;
}
