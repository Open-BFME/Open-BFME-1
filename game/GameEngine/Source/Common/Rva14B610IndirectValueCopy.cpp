struct Rva14B610Value
{
    int value;
};

struct Rva14B610IndirectValue
{
    Rva14B610Value *source;

    Rva14B610Value *copyTo(Rva14B610Value *destination);
};

// ?d_0014b610@@YAXXZ
Rva14B610Value *Rva14B610IndirectValue::copyTo(Rva14B610Value *destination)
{
    *destination = *source;
    return destination;
}
