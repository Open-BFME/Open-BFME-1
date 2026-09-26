struct RvaCACA0IdentityWithArgumentThunk
{
    RvaCACA0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000caca0@@YAXXZ
RvaCACA0IdentityWithArgumentThunk *RvaCACA0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
