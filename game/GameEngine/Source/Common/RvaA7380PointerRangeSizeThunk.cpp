struct RvaA7380PointerRangeSizeThunk
{
    int *begin;
    int *unused;
    int *end;

    int size() const;
};

// ?d_000a7380@@YAXXZ
int RvaA7380PointerRangeSizeThunk::size() const
{
    return end - begin;
}
