struct SecondaryIdentityWithArgumentThunk
{
    SecondaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_00066430@@YAXXZ
SecondaryIdentityWithArgumentThunk *SecondaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
