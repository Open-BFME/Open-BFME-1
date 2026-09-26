struct ScalarCopyAssignThunk
{
    unsigned long value;

    ScalarCopyAssignThunk &assign(const ScalarCopyAssignThunk &other);
    ScalarCopyAssignThunk &assignAlternate(const ScalarCopyAssignThunk &other);
    ScalarCopyAssignThunk &assignThird(const ScalarCopyAssignThunk &other);
};

// ?d_0036c920@@YAXXZ
ScalarCopyAssignThunk &ScalarCopyAssignThunk::assign(const ScalarCopyAssignThunk &other)
{
    value = other.value;
    return *this;
}

// ?d_0036c950@@YAXXZ
ScalarCopyAssignThunk &ScalarCopyAssignThunk::assignAlternate(const ScalarCopyAssignThunk &other)
{
    value = other.value;
    return *this;
}

// ?d_0036c970@@YAXXZ
ScalarCopyAssignThunk &ScalarCopyAssignThunk::assignThird(const ScalarCopyAssignThunk &other)
{
    value = other.value;
    return *this;
}
