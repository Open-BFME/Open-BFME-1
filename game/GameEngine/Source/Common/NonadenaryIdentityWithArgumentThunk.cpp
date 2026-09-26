struct NonadenaryIdentityWithArgumentThunk
{
    NonadenaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0006cd10@@YAXXZ
NonadenaryIdentityWithArgumentThunk *NonadenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
