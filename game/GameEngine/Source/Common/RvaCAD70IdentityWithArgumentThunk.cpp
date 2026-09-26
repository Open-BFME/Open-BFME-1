struct RvaCAD70IdentityWithArgumentThunk
{
    RvaCAD70IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cad70@@YAXXZ
RvaCAD70IdentityWithArgumentThunk *RvaCAD70IdentityWithArgumentThunk::identity(int)
{
    return this;
}
