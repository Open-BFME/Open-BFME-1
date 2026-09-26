struct Rva97920IdentityWithArgumentThunk
{
    Rva97920IdentityWithArgumentThunk *identity(int unused);
};

// ?d_00097920@@YAXXZ
Rva97920IdentityWithArgumentThunk *Rva97920IdentityWithArgumentThunk::identity(int)
{
    return this;
}
