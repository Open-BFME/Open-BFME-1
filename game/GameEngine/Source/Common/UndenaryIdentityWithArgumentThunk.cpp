struct UndenaryIdentityWithArgumentThunk
{
    UndenaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0006c650@@YAXXZ
UndenaryIdentityWithArgumentThunk *UndenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
