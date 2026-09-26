struct Rva9ED60SingleValueCopyThunk
{
    int value;

    Rva9ED60SingleValueCopyThunk *copy(const Rva9ED60SingleValueCopyThunk *source);
};

// ?d_0009ed60@@YAXXZ
Rva9ED60SingleValueCopyThunk *Rva9ED60SingleValueCopyThunk::copy(
    const Rva9ED60SingleValueCopyThunk *source)
{
    value = source->value;
    return this;
}
