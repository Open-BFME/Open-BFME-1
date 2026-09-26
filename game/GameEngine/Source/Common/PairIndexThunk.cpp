struct PairIndexValue
{
    unsigned long first;
    unsigned long second;
};

struct PairIndexThunk
{
    PairIndexValue *values;

    PairIndexValue *at(unsigned long index) const;
};

// ?d_0036d0a0@@YAXXZ
PairIndexValue *PairIndexThunk::at(unsigned long index) const
{
    return values + index;
}
