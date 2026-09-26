struct SecondShardSevenIdentityWithArgumentThunk
{
    SecondShardSevenIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0007f770@@YAXXZ
SecondShardSevenIdentityWithArgumentThunk *SecondShardSevenIdentityWithArgumentThunk::identity(int)
{
    return this;
}
