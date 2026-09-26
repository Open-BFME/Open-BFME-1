struct Rva14B420Value
{
    int value;
};

struct Rva14B420IndirectValue
{
    Rva14B420Value *source;

    Rva14B420Value *copyTo(Rva14B420Value *destination);
};

// ?d_0014b420@@YAXXZ
Rva14B420Value *Rva14B420IndirectValue::copyTo(Rva14B420Value *destination)
{
    *destination = *source;
    return destination;
}
