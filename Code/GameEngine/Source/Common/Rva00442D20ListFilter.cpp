// Address-qualified 0x00442D20 list filter; no caller proves the owner name.
class Object
{
public:
    bool isLocallyControlled() const;
};

struct Rva00442D20Entry
{
    char pad[0xFC];
    Object *object;
};

struct Rva00442D20Node
{
    Rva00442D20Node *next;
    Rva00442D20Node *previous;
    Rva00442D20Entry *value;
};

namespace _STL
{
template <bool threads, int instance>
class __node_alloc
{
public:
    static void _M_deallocate(void *p, unsigned int size);
};
class __new_alloc
{
public:
    static void *allocate(unsigned int size);
};
}

inline void *operator new(unsigned int, void *where) { return where; }

class Rva00442D20List
{
public:
    Rva00442D20Node *begin() const { return node->next; }
    Rva00442D20Node *end() const { return node; }
    void clear()
    {
        Rva00442D20Node *it = node->next;
        while (it != node) {
            Rva00442D20Node *old = it;
            it = it->next;
            _STL::__node_alloc<true, 0>::_M_deallocate(old, sizeof(Rva00442D20Node));
        }
        node->next = node;
        node->previous = node;
    }
    void push_back(Rva00442D20Entry *value)
    {
        Rva00442D20Node *position = node;
        Rva00442D20Node *fresh =
            (Rva00442D20Node *)_STL::__new_alloc::allocate(sizeof(Rva00442D20Node));
        new (&fresh->value) Rva00442D20Entry *(value);
        Rva00442D20Node *previous = position->previous;
        fresh->next = position;
        fresh->previous = previous;
        previous->next = fresh;
        position->previous = fresh;
    }
private:
    Rva00442D20Node *node;
};

class Rva00442D20Owner
{
public:
    Rva00442D20List *filterLocalEntries();
private:
    char pad[0x18];
    Rva00442D20List source;
    Rva00442D20List filtered;
};

Rva00442D20List *Rva00442D20Owner::filterLocalEntries()
{
    filtered.clear();
    for (Rva00442D20Node *it = source.begin(); it != source.end(); it = it->next) {
        Rva00442D20Entry *entry = it->value;
        if (entry && entry->object && entry->object->isLocallyControlled())
            filtered.push_back(entry);
    }
    return &filtered;
}
