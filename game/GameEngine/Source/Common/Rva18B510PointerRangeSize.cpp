struct Rva18B510PointerRangeSize
{
    unsigned int unused;
    int *begin;
    int *end;

    int size();
};

int Rva18B510PointerRangeSize::size()
{
    return end - begin;
}
