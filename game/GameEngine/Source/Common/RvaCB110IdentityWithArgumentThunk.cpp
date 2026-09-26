struct RvaCB110IdentityWithArgumentThunk
{
    RvaCB110IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cb110@@YAXXZ
RvaCB110IdentityWithArgumentThunk *RvaCB110IdentityWithArgumentThunk::identity(int)
{
    return this;
}
