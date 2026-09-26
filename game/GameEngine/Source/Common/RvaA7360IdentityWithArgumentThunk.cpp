struct RvaA7360IdentityWithArgumentThunk
{
    RvaA7360IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000a7360@@YAXXZ
RvaA7360IdentityWithArgumentThunk *RvaA7360IdentityWithArgumentThunk::identity(int)
{
    return this;
}
