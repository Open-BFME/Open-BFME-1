struct Rva192250IdentityWithArgumentThunk
{
    Rva192250IdentityWithArgumentThunk *identity(int unused);
};

// ?d_00192250@@YAXXZ
Rva192250IdentityWithArgumentThunk *Rva192250IdentityWithArgumentThunk::identity(int)
{
    return this;
}
