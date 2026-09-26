struct NonaryIdentityWithArgumentThunk
{
    NonaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0006b8f0@@YAXXZ
NonaryIdentityWithArgumentThunk *NonaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
