struct OctonaryIdentityWithArgumentThunk
{
    OctonaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0006b8e0@@YAXXZ
OctonaryIdentityWithArgumentThunk *OctonaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
