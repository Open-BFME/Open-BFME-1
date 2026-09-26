struct VigenaryIdentityWithArgumentThunk
{
    VigenaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0006cda0@@YAXXZ
VigenaryIdentityWithArgumentThunk *VigenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
