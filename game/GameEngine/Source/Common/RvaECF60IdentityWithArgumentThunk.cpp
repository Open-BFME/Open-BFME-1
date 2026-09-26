struct RvaECF60IdentityWithArgumentThunk
{
    RvaECF60IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000ecf60@@YAXXZ
RvaECF60IdentityWithArgumentThunk *RvaECF60IdentityWithArgumentThunk::identity(int)
{
    return this;
}
