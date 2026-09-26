struct DuodenaryIdentityWithArgumentThunk
{
    DuodenaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0006c660@@YAXXZ
DuodenaryIdentityWithArgumentThunk *DuodenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
