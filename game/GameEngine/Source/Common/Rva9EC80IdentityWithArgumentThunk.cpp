struct Rva9EC80IdentityWithArgumentThunk
{
    Rva9EC80IdentityWithArgumentThunk *identity(int unused);
};

// ?d_0009ec80@@YAXXZ
Rva9EC80IdentityWithArgumentThunk *Rva9EC80IdentityWithArgumentThunk::identity(int)
{
    return this;
}
