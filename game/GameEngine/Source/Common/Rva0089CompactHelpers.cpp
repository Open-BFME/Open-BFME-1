// cl: /DNDEBUG /MD /O2

struct Rva008923E0Index
{
    int m_position;
    int m_unused;
    int *m_items;
    int at(int offset) const;
};
int Rva008923E0Index::at(int offset) const { return m_items[m_position - offset - 1]; }

struct Rva00892900Index
{
    int m_position;
    int m_unused;
    int *m_items;
    int at(int offset) const;
};
int Rva00892900Index::at(int offset) const { return m_items[m_position - offset - 1]; }

bool Rva00892620NotEqual(const int *value, int other)
{
    return *value != other;
}

bool Rva00894F60Equal(const int *value, int other)
{
    return *value == other;
}

struct Rva00894CD0Triple
{
    char m_unknown[12];
    int m_first;
    int m_second;
    int m_third;
    void set(int first, int second, int third);
};
void Rva00894CD0Triple::set(int first, int second, int third)
{
    m_first = first;
    m_second = second;
    m_third = third;
}

struct Rva00894E60Ref
{
    int *m_pointer;
    Rva00894E60Ref(int *pointer);
};
Rva00894E60Ref::Rva00894E60Ref(int *pointer) : m_pointer(pointer)
{
    if (pointer) ++*pointer;
}

struct Rva00894E80Ref
{
    int *m_pointer;
    Rva00894E80Ref(const Rva00894E80Ref &other);
};
Rva00894E80Ref::Rva00894E80Ref(const Rva00894E80Ref &other) : m_pointer(other.m_pointer)
{
    if (m_pointer) ++*m_pointer;
}

struct Rva00894F00Pair
{
    int m_pointer;
    int m_extra;
    Rva00894F00Pair(const int *pointer, int extra);
};
Rva00894F00Pair::Rva00894F00Pair(const int *pointer, int extra) : m_pointer(*pointer), m_extra(extra) {}
