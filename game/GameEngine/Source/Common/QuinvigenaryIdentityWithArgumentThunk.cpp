struct QuinvigenaryIdentityWithArgumentThunk
{
    QuinvigenaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0006dfe0@@YAXXZ
QuinvigenaryIdentityWithArgumentThunk *QuinvigenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
