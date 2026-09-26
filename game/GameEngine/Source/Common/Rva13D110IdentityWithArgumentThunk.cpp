struct Rva13D110IdentityWithArgumentThunk
{
    Rva13D110IdentityWithArgumentThunk *identity(int unused);
};

// ?d_0013d110@@YAXXZ
Rva13D110IdentityWithArgumentThunk *Rva13D110IdentityWithArgumentThunk::identity(int)
{
    return this;
}
