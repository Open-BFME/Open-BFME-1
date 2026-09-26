struct RvaE6D20IdentityWithArgumentThunk
{
    RvaE6D20IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000e6d20@@YAXXZ
RvaE6D20IdentityWithArgumentThunk *RvaE6D20IdentityWithArgumentThunk::identity(int)
{
    return this;
}
