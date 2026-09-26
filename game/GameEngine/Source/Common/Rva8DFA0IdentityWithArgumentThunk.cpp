struct Rva8DFA0IdentityWithArgumentThunk
{
    Rva8DFA0IdentityWithArgumentThunk *identity(int unused);
};

// ?d_0008dfa0@@YAXXZ
Rva8DFA0IdentityWithArgumentThunk *Rva8DFA0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
