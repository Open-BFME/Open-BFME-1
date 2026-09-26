struct DuotricenaryIdentityWithArgumentThunk
{
    DuotricenaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_000929d0@@YAXXZ
DuotricenaryIdentityWithArgumentThunk *DuotricenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
