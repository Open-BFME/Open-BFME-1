struct IdentityWithArgumentThunk
{
    IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000653b0@@YAXXZ
IdentityWithArgumentThunk *IdentityWithArgumentThunk::identity(int)
{
    return this;
}
