struct ThreeWordAssignmentThunk
{
    unsigned long first;
    unsigned long second;
    unsigned long third;

    void assign(unsigned long firstValue, unsigned long secondValue, unsigned long thirdValue);
};

// ?d_00061690@@YAXXZ
void ThreeWordAssignmentThunk::assign(
    unsigned long firstValue, unsigned long secondValue, unsigned long thirdValue)
{
    first = firstValue;
    second = secondValue;
    third = thirdValue;
}
