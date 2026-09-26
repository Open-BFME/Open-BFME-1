unsigned long __stdcall alignUp(unsigned long value, unsigned long alignment)
{
    return (value + alignment - 1) & ~(alignment - 1);
}
