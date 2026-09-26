struct Rva191F70IdentityWithArgumentThunk
{
    Rva191F70IdentityWithArgumentThunk *identity(int unused);
};

// ?d_00191f70@@YAXXZ
Rva191F70IdentityWithArgumentThunk *Rva191F70IdentityWithArgumentThunk::identity(int)
{
    return this;
}
