struct DoubleZeroCtorThunk
{
    unsigned long first;
    unsigned long second;

    DoubleZeroCtorThunk();
};

// ?d_0036cc10@@YAXXZ
DoubleZeroCtorThunk::DoubleZeroCtorThunk() : first(0), second(0)
{
}
