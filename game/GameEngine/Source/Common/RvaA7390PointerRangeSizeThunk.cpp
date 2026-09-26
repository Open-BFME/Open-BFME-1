struct RvaA7390RangeElement
{
    int words[2];
};

struct RvaA7390PointerRangeSizeThunk
{
    RvaA7390RangeElement *begin;
    RvaA7390RangeElement *unused;
    RvaA7390RangeElement *end;

    int size() const;
};

int RvaA7390PointerRangeSizeThunk::size() const
{
    return end - begin;
}
