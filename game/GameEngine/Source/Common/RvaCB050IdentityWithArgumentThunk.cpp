struct RvaCB050IdentityWithArgumentThunk
{
    RvaCB050IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cb050@@YAXXZ
RvaCB050IdentityWithArgumentThunk *RvaCB050IdentityWithArgumentThunk::identity(int)
{
    return this;
}
