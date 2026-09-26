struct OctovigenaryIdentityWithArgumentThunk
{
    OctovigenaryIdentityWithArgumentThunk *identity(int unused);
};

// ?d_0008dfd0@@YAXXZ
OctovigenaryIdentityWithArgumentThunk *OctovigenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
