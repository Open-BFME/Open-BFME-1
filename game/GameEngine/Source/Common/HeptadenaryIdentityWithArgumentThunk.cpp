struct HeptadenaryIdentityWithArgumentThunk
{
    HeptadenaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0006cca0@@YAXXZ
HeptadenaryIdentityWithArgumentThunk *HeptadenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
