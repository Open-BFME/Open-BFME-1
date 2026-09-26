struct RvaCB040IdentityWithArgumentThunk
{
    RvaCB040IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cb040@@YAXXZ
RvaCB040IdentityWithArgumentThunk *RvaCB040IdentityWithArgumentThunk::identity(int)
{
    return this;
}
