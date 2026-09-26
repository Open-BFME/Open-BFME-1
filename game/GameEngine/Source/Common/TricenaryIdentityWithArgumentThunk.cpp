struct TricenaryIdentityWithArgumentThunk
{
    TricenaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0008f4d0@@YAXXZ
TricenaryIdentityWithArgumentThunk *TricenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
