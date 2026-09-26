struct RvaECFF0IdentityWithArgumentThunk
{
    RvaECFF0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000ecff0@@YAXXZ
RvaECFF0IdentityWithArgumentThunk *RvaECFF0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
