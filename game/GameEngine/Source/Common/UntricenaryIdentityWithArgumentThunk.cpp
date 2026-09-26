struct UntricenaryIdentityWithArgumentThunk
{
    UntricenaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0008f4e0@@YAXXZ
UntricenaryIdentityWithArgumentThunk *UntricenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
