struct FirstWordSetterThunk
{
    unsigned long value;

    FirstWordSetterThunk *set(unsigned long newValue);
    FirstWordSetterThunk *setAlternate(unsigned long newValue);
    void assign(unsigned long newValue);
};

// ?d_0005ba30@@YAXXZ
FirstWordSetterThunk *FirstWordSetterThunk::set(unsigned long newValue)
{
    value = newValue;
    return this;
}

// ?d_00061cd0@@YAXXZ
FirstWordSetterThunk *FirstWordSetterThunk::setAlternate(unsigned long newValue)
{
    value = newValue;
    return this;
}

// ?d_0005bb60@@YAXXZ
void FirstWordSetterThunk::assign(unsigned long newValue)
{
    value = newValue;
}
