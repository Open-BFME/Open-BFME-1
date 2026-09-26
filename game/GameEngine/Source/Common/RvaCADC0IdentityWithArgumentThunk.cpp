struct RvaCADC0IdentityWithArgumentThunk
{
    RvaCADC0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cadc0@@YAXXZ
RvaCADC0IdentityWithArgumentThunk *RvaCADC0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
