struct Rva14B3F0Storage
{
    char *base;
};

struct Rva14B3F0IndirectView
{
    Rva14B3F0Storage *storage;

    char *payload();
};

// ?d_0014b3f0@@YAXXZ
char *Rva14B3F0IndirectView::payload()
{
    return storage->base + 8;
}
