struct FifthShardSevenIdentityWithArgumentThunk
{
    FifthShardSevenIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0007f800@@YAXXZ
FifthShardSevenIdentityWithArgumentThunk *FifthShardSevenIdentityWithArgumentThunk::identity(int)
{
    return this;
}
