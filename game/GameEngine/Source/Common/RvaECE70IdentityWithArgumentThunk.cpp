struct RvaECE70IdentityWithArgumentThunk
{
    RvaECE70IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000ece70@@YAXXZ
RvaECE70IdentityWithArgumentThunk *RvaECE70IdentityWithArgumentThunk::identity(int)
{
    return this;
}
