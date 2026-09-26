struct QuinaryIdentityWithArgumentThunk
{
    QuinaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_00068a40@@YAXXZ
QuinaryIdentityWithArgumentThunk *QuinaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
