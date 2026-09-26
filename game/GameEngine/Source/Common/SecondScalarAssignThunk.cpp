struct SecondScalarAssignThunk
{
    unsigned long value;

    SecondScalarAssignThunk &assign(unsigned long ignored, unsigned long newValue);
    SecondScalarAssignThunk &assignAlternate(unsigned long ignored, unsigned long newValue);
    SecondScalarAssignThunk &assignThird(unsigned long ignored, unsigned long newValue);
    SecondScalarAssignThunk &assignFourth(unsigned long ignored, unsigned long newValue);
};

// ?d_0036d350@@YAXXZ
SecondScalarAssignThunk &SecondScalarAssignThunk::assign(unsigned long, unsigned long newValue)
{
    value = newValue;
    return *this;
}

// ?d_0036d360@@YAXXZ
SecondScalarAssignThunk &SecondScalarAssignThunk::assignAlternate(unsigned long, unsigned long newValue)
{
    value = newValue;
    return *this;
}

// ?d_0036d390@@YAXXZ
SecondScalarAssignThunk &SecondScalarAssignThunk::assignThird(unsigned long, unsigned long newValue)
{
    value = newValue;
    return *this;
}

// ?d_0036d410@@YAXXZ
SecondScalarAssignThunk &SecondScalarAssignThunk::assignFourth(unsigned long, unsigned long newValue)
{
    value = newValue;
    return *this;
}
