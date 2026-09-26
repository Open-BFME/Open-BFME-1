struct ScalarAssignThunk
{
    unsigned long value;

    ScalarAssignThunk &assign(unsigned long newValue);
    ScalarAssignThunk &assignAlternate(unsigned long newValue);
};

// ?d_0036c810@@YAXXZ
ScalarAssignThunk &ScalarAssignThunk::assign(unsigned long newValue)
{
    value = newValue;
    return *this;
}

// ?d_0036c880@@YAXXZ
ScalarAssignThunk &ScalarAssignThunk::assignAlternate(unsigned long newValue)
{
    value = newValue;
    return *this;
}
