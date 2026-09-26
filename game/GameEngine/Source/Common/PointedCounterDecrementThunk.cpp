struct PointedCounterDecrementThunk
{
    int *counter;

    void decrement();
};

// ?d_0009ffb0@@YAXXZ
void PointedCounterDecrementThunk::decrement()
{
    --*counter;
}
