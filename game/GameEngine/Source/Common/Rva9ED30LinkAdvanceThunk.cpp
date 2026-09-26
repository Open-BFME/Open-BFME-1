struct Rva9ED30LinkAdvanceThunk
{
    Rva9ED30LinkAdvanceThunk *next;

    Rva9ED30LinkAdvanceThunk *advanceLink();
};

// ?d_0009ed30@@YAXXZ
Rva9ED30LinkAdvanceThunk *Rva9ED30LinkAdvanceThunk::advanceLink()
{
    next = next->next;
    return this;
}
