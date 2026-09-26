struct RvaCADA0IdentityWithArgumentThunk
{
    RvaCADA0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cada0@@YAXXZ
RvaCADA0IdentityWithArgumentThunk *RvaCADA0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
