struct FourthShardSevenIdentityWithArgumentThunk
{
    FourthShardSevenIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0007f7f0@@YAXXZ
FourthShardSevenIdentityWithArgumentThunk *FourthShardSevenIdentityWithArgumentThunk::identity(int)
{
    return this;
}
