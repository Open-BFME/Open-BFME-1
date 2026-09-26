struct Rva14AA20OffsetView
{
    char *base;

    char *payload();
};

// ?d_0014aa20@@YAXXZ
char *Rva14AA20OffsetView::payload()
{
    return base + 8;
}
