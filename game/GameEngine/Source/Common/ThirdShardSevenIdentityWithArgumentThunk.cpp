struct ThirdShardSevenIdentityWithArgumentThunk
{
    ThirdShardSevenIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0007f7a0@@YAXXZ
ThirdShardSevenIdentityWithArgumentThunk *ThirdShardSevenIdentityWithArgumentThunk::identity(int)
{
    return this;
}
