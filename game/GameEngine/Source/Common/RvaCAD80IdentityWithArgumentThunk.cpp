struct RvaCAD80IdentityWithArgumentThunk
{
    RvaCAD80IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cad80@@YAXXZ
RvaCAD80IdentityWithArgumentThunk *RvaCAD80IdentityWithArgumentThunk::identity(int)
{
    return this;
}
