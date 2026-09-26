struct RvaED000IdentityWithArgumentThunk
{
    RvaED000IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000ed000@@YAXXZ
RvaED000IdentityWithArgumentThunk *RvaED000IdentityWithArgumentThunk::identity(int)
{
    return this;
}
