struct RvaCAC90IdentityWithArgumentThunk
{
    RvaCAC90IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cac90@@YAXXZ
RvaCAC90IdentityWithArgumentThunk *RvaCAC90IdentityWithArgumentThunk::identity(int)
{
    return this;
}
