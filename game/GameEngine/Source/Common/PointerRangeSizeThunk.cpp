struct PointerRangeSizeThunk
{
    int *begin;
    int *end;

    int size() const;
};

// ?d_0036c940@@YAXXZ
int PointerRangeSizeThunk::size() const
{
    return end - begin;
}
