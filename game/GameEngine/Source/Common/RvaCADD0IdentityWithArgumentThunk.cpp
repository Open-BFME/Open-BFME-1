struct RvaCADD0IdentityWithArgumentThunk
{
    RvaCADD0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_000cadd0@@YAXXZ
RvaCADD0IdentityWithArgumentThunk *RvaCADD0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
