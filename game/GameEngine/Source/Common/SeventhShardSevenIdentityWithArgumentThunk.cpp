struct SeventhShardSevenIdentityWithArgumentThunk
{
    SeventhShardSevenIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0007f820@@YAXXZ
SeventhShardSevenIdentityWithArgumentThunk *SeventhShardSevenIdentityWithArgumentThunk::identity(int)
{
    return this;
}
