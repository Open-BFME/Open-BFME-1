struct NestedFieldValues
{
    unsigned long prefix[6];
    unsigned long first;
    unsigned long second;
    unsigned long third;
};

struct NestedFieldGetterThunk
{
    unsigned long unused;
    NestedFieldValues *values;

    unsigned long getFirst() const;
    unsigned long getSecond() const;
    unsigned long getThird() const;
};

// ?d_0036cf40@@YAXXZ
unsigned long NestedFieldGetterThunk::getFirst() const
{
    return values->first;
}

// ?d_0036cf50@@YAXXZ
unsigned long NestedFieldGetterThunk::getSecond() const
{
    return values->second;
}

// ?d_0036cf60@@YAXXZ
unsigned long NestedFieldGetterThunk::getThird() const
{
    return values->third;
}
