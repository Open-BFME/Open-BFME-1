struct OctadenaryIdentityWithArgumentThunk
{
    OctadenaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0006ccb0@@YAXXZ
OctadenaryIdentityWithArgumentThunk *OctadenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
