struct HexadenaryIdentityWithArgumentThunk
{
    HexadenaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0006cc90@@YAXXZ
HexadenaryIdentityWithArgumentThunk *HexadenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
