struct DenaryIdentityWithArgumentThunk
{
    DenaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0006b900@@YAXXZ
DenaryIdentityWithArgumentThunk *DenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
