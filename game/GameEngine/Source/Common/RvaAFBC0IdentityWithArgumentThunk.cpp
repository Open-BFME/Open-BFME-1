struct RvaAFBC0IdentityWithArgumentThunk
{
    RvaAFBC0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000afbc0@@YAXXZ
RvaAFBC0IdentityWithArgumentThunk *RvaAFBC0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
