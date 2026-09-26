struct RvaA7370IdentityWithArgumentThunk
{
    RvaA7370IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000a7370@@YAXXZ
RvaA7370IdentityWithArgumentThunk *RvaA7370IdentityWithArgumentThunk::identity(int)
{
    return this;
}
