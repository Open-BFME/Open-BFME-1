struct TertiaryIdentityWithArgumentThunk
{
    TertiaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_00066480@@YAXXZ
TertiaryIdentityWithArgumentThunk *TertiaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
