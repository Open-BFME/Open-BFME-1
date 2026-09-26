struct TetradenaryIdentityWithArgumentThunk
{
    TetradenaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0006cc30@@YAXXZ
TetradenaryIdentityWithArgumentThunk *TetradenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
