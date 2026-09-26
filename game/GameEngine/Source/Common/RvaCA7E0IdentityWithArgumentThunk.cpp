struct RvaCA7E0IdentityWithArgumentThunk
{
    RvaCA7E0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000ca7e0@@YAXXZ
RvaCA7E0IdentityWithArgumentThunk *RvaCA7E0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
