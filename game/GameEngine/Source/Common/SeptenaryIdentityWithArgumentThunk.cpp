struct SeptenaryIdentityWithArgumentThunk
{
    SeptenaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0006b4c0@@YAXXZ
SeptenaryIdentityWithArgumentThunk *SeptenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
