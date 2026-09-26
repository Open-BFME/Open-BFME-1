struct RvaCAE90IdentityWithArgumentThunk
{
    RvaCAE90IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cae90@@YAXXZ
RvaCAE90IdentityWithArgumentThunk *RvaCAE90IdentityWithArgumentThunk::identity(int)
{
    return this;
}
