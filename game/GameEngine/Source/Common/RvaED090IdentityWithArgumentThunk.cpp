struct RvaED090IdentityWithArgumentThunk
{
    RvaED090IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000ed090@@YAXXZ
RvaED090IdentityWithArgumentThunk *RvaED090IdentityWithArgumentThunk::identity(int)
{
    return this;
}
