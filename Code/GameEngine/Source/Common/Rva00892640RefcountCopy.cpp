// cl: /DNDEBUG /MD /EHs-c-
// Copy a run of two-word refcounted items, preserving the retail STL shape.

struct Rva00892640Handle
{
    unsigned short refs;
};

struct Rva00892640Item
{
    Rva00892640Handle *handle;
    void *extra;
};

typedef void (*Rva00892640Destroy)(Rva00892640Handle *);

struct Rva00892640Deleter
{
    void *pad;
    Rva00892640Destroy destroy;
};

extern Rva00892640Deleter *g_rva00892640Deleter;

// ?Rva00892640CopyItems@@YAPAURva00892640Item@@PAU1@00@Z
Rva00892640Item *Rva00892640CopyItems(
    Rva00892640Item *first, Rva00892640Item *last,
    Rva00892640Item *dest)
{
    Rva00892640Item *src = first;
    Rva00892640Item *end = last;
    if (src != end)
    {
        do
        {
            Rva00892640Handle *incoming = src->handle;
            Rva00892640Item *slot = dest++;
            ++incoming->refs;
            Rva00892640Handle *old = slot->handle;
            --old->refs;
            if (old->refs == 0)
                g_rva00892640Deleter->destroy(old);
            slot->handle = src->handle;
            slot->extra = src->extra;
            ++src;
        }
        while (src != end);
    }

    return dest;
}
