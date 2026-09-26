struct Rva14A9E0ValueAssignment
{
    int value;

    Rva14A9E0ValueAssignment *assign(const Rva14A9E0ValueAssignment *source);
};

// ?d_0014a9e0@@YAXXZ
Rva14A9E0ValueAssignment *Rva14A9E0ValueAssignment::assign(const Rva14A9E0ValueAssignment *source)
{
    value = source->value;
    return this;
}
