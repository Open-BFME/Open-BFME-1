struct Rva87A40IdentityWithArgumentThunk
{
    Rva87A40IdentityWithArgumentThunk *identity(int unused);
};

// ?d_00087a40@@YAXXZ
Rva87A40IdentityWithArgumentThunk *Rva87A40IdentityWithArgumentThunk::identity(int)
{
    return this;
}
