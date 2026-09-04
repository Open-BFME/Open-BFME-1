// Byte-matching reconstruction for 0x00894120.

struct Rva00894120Item
{
    void *first;
    void *second;
};

class Rva00894120Vector
{
public:
    void insert(Rva00894120Item *source);
    void helper(void *, void *, void *);

private:
    unsigned m_count;
    char m_pad04[4];
    Rva00894120Item *m_items;
};

static __forceinline Rva00894120Item *Rva00894120Next(
    Rva00894120Item *item)
{
    return item + 1;
}

// ?insert@Rva00894120Vector@@QAEXPAURva00894120Item@@@Z
void Rva00894120Vector::insert(Rva00894120Item *source)
{
    Rva00894120Item *end = &m_items[m_count];
    Rva00894120Item *next = source + 1;
    Rva00894120Item *begin = source;
    helper(&begin, &next, &end);
}
