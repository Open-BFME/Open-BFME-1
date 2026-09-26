struct TripleIndexValue
{
    unsigned long first;
    unsigned long second;
    unsigned long third;
};

struct TripleIndexThunk
{
    TripleIndexValue *values;

    TripleIndexValue *at(unsigned long index) const;
};

// ?d_0036d0b0@@YAXXZ
TripleIndexValue *TripleIndexThunk::at(unsigned long index) const
{
    return values + index;
}
