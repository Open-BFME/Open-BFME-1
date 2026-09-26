struct ShardSevenIdentityWithArgumentThunk
{
    ShardSevenIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0007f6f0@@YAXXZ
ShardSevenIdentityWithArgumentThunk *ShardSevenIdentityWithArgumentThunk::identity(int)
{
    return this;
}
