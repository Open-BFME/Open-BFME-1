struct RvaAFBB0IdentityWithArgumentThunk
{
    RvaAFBB0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000afbb0@@YAXXZ
RvaAFBB0IdentityWithArgumentThunk *RvaAFBB0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
