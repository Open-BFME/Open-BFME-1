struct RvaECF30IdentityWithArgumentThunk
{
    RvaECF30IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000ecf30@@YAXXZ
RvaECF30IdentityWithArgumentThunk *RvaECF30IdentityWithArgumentThunk::identity(int)
{
    return this;
}
