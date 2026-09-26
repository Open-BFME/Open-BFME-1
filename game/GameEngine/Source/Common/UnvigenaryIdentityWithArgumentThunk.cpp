struct UnvigenaryIdentityWithArgumentThunk
{
    UnvigenaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0006cdb0@@YAXXZ
UnvigenaryIdentityWithArgumentThunk *UnvigenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
