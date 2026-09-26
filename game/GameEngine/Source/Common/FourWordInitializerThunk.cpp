struct FourWordInitializerThunk
{
    unsigned long tag;
    unsigned long first;
    unsigned long second;
    unsigned long third;

    FourWordInitializerThunk *initialize(unsigned long firstValue, unsigned long secondValue, unsigned long thirdValue);
};

// ?d_0005bac0@@YAXXZ
FourWordInitializerThunk *FourWordInitializerThunk::initialize(
    unsigned long firstValue, unsigned long secondValue, unsigned long thirdValue)
{
    tag = 1;
    first = firstValue;
    second = secondValue;
    third = thirdValue;
    return this;
}
