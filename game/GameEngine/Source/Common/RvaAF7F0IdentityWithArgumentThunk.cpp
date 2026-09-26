struct RvaAF7F0IdentityWithArgumentThunk
{
    RvaAF7F0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000af7f0@@YAXXZ
RvaAF7F0IdentityWithArgumentThunk *RvaAF7F0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
