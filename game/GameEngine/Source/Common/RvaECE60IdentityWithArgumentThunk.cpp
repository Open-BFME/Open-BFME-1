struct RvaECE60IdentityWithArgumentThunk
{
    RvaECE60IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000ece60@@YAXXZ
RvaECE60IdentityWithArgumentThunk *RvaECE60IdentityWithArgumentThunk::identity(int)
{
    return this;
}
