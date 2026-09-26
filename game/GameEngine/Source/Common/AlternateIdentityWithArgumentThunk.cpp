struct AlternateIdentityWithArgumentThunk
{
    AlternateIdentityWithArgumentThunk *identity(int unused);
};

AlternateIdentityWithArgumentThunk *AlternateIdentityWithArgumentThunk::identity(int)
{
    return this;
}
