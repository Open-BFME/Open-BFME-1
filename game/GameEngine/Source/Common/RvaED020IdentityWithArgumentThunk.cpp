struct RvaED020IdentityWithArgumentThunk
{
    RvaED020IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000ed020@@YAXXZ
RvaED020IdentityWithArgumentThunk *RvaED020IdentityWithArgumentThunk::identity(int)
{
    return this;
}
