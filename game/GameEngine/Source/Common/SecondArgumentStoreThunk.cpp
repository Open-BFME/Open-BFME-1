struct SecondArgumentStoreThunk
{
    unsigned long value;

    SecondArgumentStoreThunk *setFromSecondArgument(unsigned long unused, unsigned long newValue);
};

// ?d_00415b60@@YAXXZ
SecondArgumentStoreThunk *SecondArgumentStoreThunk::setFromSecondArgument(unsigned long, unsigned long newValue)
{
    value = newValue;
    return this;
}
