struct RvaB94A0IdentityWithArgumentThunk
{
    RvaB94A0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000b94a0@@YAXXZ
RvaB94A0IdentityWithArgumentThunk *RvaB94A0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
