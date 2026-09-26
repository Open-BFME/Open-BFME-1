struct Rva14B400Pair
{
    int first;
    int second;

    Rva14B400Pair *reset();
};

// ?d_0014b400@@YAXXZ
Rva14B400Pair *Rva14B400Pair::reset()
{
    first = 0;
    second = 0;
    return this;
}
