struct Rva192260IdentityWithArgumentThunk
{
    Rva192260IdentityWithArgumentThunk *identity(int unused);
};

// ?d_00192260@@YAXXZ
Rva192260IdentityWithArgumentThunk *Rva192260IdentityWithArgumentThunk::identity(int)
{
    return this;
}
