struct DuovigenaryIdentityWithArgumentThunk
{
    DuovigenaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0006cdc0@@YAXXZ
DuovigenaryIdentityWithArgumentThunk *DuovigenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
