struct RvaA8BA0IdentityWithArgumentThunk
{
    RvaA8BA0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000a8ba0@@YAXXZ
RvaA8BA0IdentityWithArgumentThunk *RvaA8BA0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
