struct TridenaryIdentityWithArgumentThunk
{
    TridenaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0006c670@@YAXXZ
TridenaryIdentityWithArgumentThunk *TridenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
