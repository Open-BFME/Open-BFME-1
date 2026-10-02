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

struct BfmeStringPool3AF0
{
    void *m_alloc;
    void (__cdecl *m_free)(void *storage);
};

extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;

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
                g_rva01337A30AllocPair->m_free(old);
            slot->handle = src->handle;
            slot->extra = src->extra;
            ++src;
        }
        while (src != end);
    }

    return dest;
}

// ?Rva008926D0CopyItems@@YAPAURva00892640Item@@PAU1@00@Z
Rva00892640Item *Rva008926D0CopyItems(
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
                g_rva01337A30AllocPair->m_free(old);
            slot->handle = src->handle;
            slot->extra = src->extra;
            ++src;
        }
        while (src != end);
    }

    return dest;
}

// ?Rva00892730CopyItems@@YAPAURva00892640Item@@PAU1@00@Z
Rva00892640Item *Rva00892730CopyItems(
    Rva00892640Item *first, Rva00892640Item *last,
    Rva00892640Item *dest)
{
    int count = (int)(last - first);
    last--;
    dest += count - 1;
    if (count)
    {
        int i = count;
        do
        {
            Rva00892640Handle *incoming = last->handle;
            ++incoming->refs;
            Rva00892640Item *slot = dest;
            Rva00892640Handle *old = slot->handle;
            --old->refs;
            if (old->refs == 0)
                g_rva01337A30AllocPair->m_free(old);
            slot->handle = last->handle;
            slot->extra = last->extra;
            last--;
            dest--;
        }
        while (--i);
    }
    return dest;
}
