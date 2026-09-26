struct SenaryIdentityWithArgumentThunk
{
    SenaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_000694c0@@YAXXZ
SenaryIdentityWithArgumentThunk *SenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
