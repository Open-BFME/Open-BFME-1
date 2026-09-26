struct RvaCAE80IdentityWithArgumentThunk
{
    RvaCAE80IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cae80@@YAXXZ
RvaCAE80IdentityWithArgumentThunk *RvaCAE80IdentityWithArgumentThunk::identity(int)
{
    return this;
}
