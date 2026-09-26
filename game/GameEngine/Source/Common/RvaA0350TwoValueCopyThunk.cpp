struct RvaA0350TwoValueCopyThunk
{
    int first;
    int second;

    RvaA0350TwoValueCopyThunk *copy(const RvaA0350TwoValueCopyThunk *source);
};

// ?d_000a0350@@YAXXZ
RvaA0350TwoValueCopyThunk *RvaA0350TwoValueCopyThunk::copy(
    const RvaA0350TwoValueCopyThunk *source)
{
    first = source->first;
    second = source->second;
    return this;
}
