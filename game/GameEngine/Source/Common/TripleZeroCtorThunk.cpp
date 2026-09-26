struct TripleZeroCtorThunk
{
    unsigned long first;
    unsigned long second;
    unsigned long third;

    TripleZeroCtorThunk();
};

// ?d_0036cb30@@YAXXZ
TripleZeroCtorThunk::TripleZeroCtorThunk() : first(0), second(0), third(0)
{
}
