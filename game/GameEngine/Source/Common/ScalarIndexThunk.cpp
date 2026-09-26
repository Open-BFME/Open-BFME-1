struct ScalarIndexThunk
{
    unsigned long *values;

    unsigned long *at(unsigned long index) const;
};

// ?d_0036d0e0@@YAXXZ
unsigned long *ScalarIndexThunk::at(unsigned long index) const
{
    return values + index;
}
