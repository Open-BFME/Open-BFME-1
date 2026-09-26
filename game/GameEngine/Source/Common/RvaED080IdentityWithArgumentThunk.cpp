struct RvaED080IdentityWithArgumentThunk
{
    RvaED080IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000ed080@@YAXXZ
RvaED080IdentityWithArgumentThunk *RvaED080IdentityWithArgumentThunk::identity(int)
{
    return this;
}
