struct RvaFC500IdentityWithArgumentThunk
{
    RvaFC500IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000fc500@@YAXXZ
RvaFC500IdentityWithArgumentThunk *RvaFC500IdentityWithArgumentThunk::identity(int)
{
    return this;
}
