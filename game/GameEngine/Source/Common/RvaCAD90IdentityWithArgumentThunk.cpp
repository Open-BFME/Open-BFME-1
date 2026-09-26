struct RvaCAD90IdentityWithArgumentThunk
{
    RvaCAD90IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cad90@@YAXXZ
RvaCAD90IdentityWithArgumentThunk *RvaCAD90IdentityWithArgumentThunk::identity(int)
{
    return this;
}
