struct Rva14B540SecondArgumentSetter
{
    int value;

    Rva14B540SecondArgumentSetter *set(int unused, int newValue);
};

// ?d_0014b540@@YAXXZ
Rva14B540SecondArgumentSetter *Rva14B540SecondArgumentSetter::set(int, int newValue)
{
    value = newValue;
    return this;
}
