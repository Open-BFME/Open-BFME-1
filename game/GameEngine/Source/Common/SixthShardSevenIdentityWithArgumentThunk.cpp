struct SixthShardSevenIdentityWithArgumentThunk
{
    SixthShardSevenIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0007f810@@YAXXZ
SixthShardSevenIdentityWithArgumentThunk *SixthShardSevenIdentityWithArgumentThunk::identity(int)
{
    return this;
}
