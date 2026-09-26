struct SeptemvigenaryIdentityWithArgumentThunk
{
    SeptemvigenaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0006e000@@YAXXZ
SeptemvigenaryIdentityWithArgumentThunk *SeptemvigenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
