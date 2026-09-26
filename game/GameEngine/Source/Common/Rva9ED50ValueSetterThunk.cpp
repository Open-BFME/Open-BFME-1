struct Rva9ED50ValueSetterThunk
{
    int value;

    Rva9ED50ValueSetterThunk *setValue(int newValue);
};

// ?d_0009ed50@@YAXXZ
Rva9ED50ValueSetterThunk *Rva9ED50ValueSetterThunk::setValue(int newValue)
{
    value = newValue;
    return this;
}
