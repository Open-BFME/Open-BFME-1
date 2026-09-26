struct TrivigenaryIdentityWithArgumentThunk
{
    TrivigenaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0006dfc0@@YAXXZ
TrivigenaryIdentityWithArgumentThunk *TrivigenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
