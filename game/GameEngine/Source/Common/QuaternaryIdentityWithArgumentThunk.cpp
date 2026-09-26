struct QuaternaryIdentityWithArgumentThunk
{
    QuaternaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_00066490@@YAXXZ
QuaternaryIdentityWithArgumentThunk *QuaternaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
