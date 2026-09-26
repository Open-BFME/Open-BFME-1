struct LongPointerRangeThunk
{
    long *begin;
    long *end;

    long size() const;
};

long LongPointerRangeThunk::size() const
{
    return end - begin;
}
