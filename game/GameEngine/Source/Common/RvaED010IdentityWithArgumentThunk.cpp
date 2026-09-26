struct RvaED010IdentityWithArgumentThunk
{
    RvaED010IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000ed010@@YAXXZ
RvaED010IdentityWithArgumentThunk *RvaED010IdentityWithArgumentThunk::identity(int)
{
    return this;
}
