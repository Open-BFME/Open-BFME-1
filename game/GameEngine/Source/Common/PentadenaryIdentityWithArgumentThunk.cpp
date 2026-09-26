struct PentadenaryIdentityWithArgumentThunk
{
    PentadenaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0006cc80@@YAXXZ
PentadenaryIdentityWithArgumentThunk *PentadenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
