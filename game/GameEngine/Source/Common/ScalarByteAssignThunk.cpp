struct ScalarByteAssignThunk
{
    unsigned long scalar;
    unsigned char flag;

    ScalarByteAssignThunk &assign(const unsigned long *newScalar, const unsigned char *newFlag);
    ScalarByteAssignThunk &assignAlternate(const unsigned long *newScalar, const unsigned char *newFlag);
    ScalarByteAssignThunk &assignThird(const unsigned long *newScalar, const unsigned char *newFlag);
};

// ?d_0036d6f0@@YAXXZ
ScalarByteAssignThunk &ScalarByteAssignThunk::assign(
    const unsigned long *newScalar,
    const unsigned char *newFlag)
{
    scalar = *newScalar;
    flag = *newFlag;
    return *this;
}

// ?d_0036d750@@YAXXZ
ScalarByteAssignThunk &ScalarByteAssignThunk::assignAlternate(
    const unsigned long *newScalar,
    const unsigned char *newFlag)
{
    scalar = *newScalar;
    flag = *newFlag;
    return *this;
}

// ?d_0036d7b0@@YAXXZ
ScalarByteAssignThunk &ScalarByteAssignThunk::assignThird(
    const unsigned long *newScalar,
    const unsigned char *newFlag)
{
    scalar = *newScalar;
    flag = *newFlag;
    return *this;
}
