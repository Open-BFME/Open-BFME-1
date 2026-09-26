struct RvaCAD10IdentityWithArgumentThunk
{
    RvaCAD10IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cad10@@YAXXZ
RvaCAD10IdentityWithArgumentThunk *RvaCAD10IdentityWithArgumentThunk::identity(int)
{
    return this;
}
