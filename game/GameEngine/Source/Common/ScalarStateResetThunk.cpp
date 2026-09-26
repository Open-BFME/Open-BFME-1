struct ScalarStateResetThunk
{
    unsigned long leading;
    unsigned long first;
    unsigned long second;
    unsigned long third;
    unsigned long fourth;
    unsigned long fifth;
    unsigned long sixth;
    unsigned char firstByte;
    unsigned char secondByte;
    unsigned char padding[2];
    long sentinel;

    unsigned long reset();
};

// ?d_0005c190@@YAXXZ
unsigned long ScalarStateResetThunk::reset()
{
    unsigned long result = first;
    first = 0;
    second = 0;
    third = 0;
    fourth = 0;
    sixth = 0;
    fifth = 0;
    sentinel = -1;
    secondByte = 0;
    firstByte = 0;
    return result;
}
