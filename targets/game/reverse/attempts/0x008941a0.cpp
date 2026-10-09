// ?find008941A0@Rva00894120Vector@@QAEXPAX@Z
// partial score=0.669 date=2026-10-09
// ?find008941A0@Rva00894120Vector@@QAEXPAX@Z
// cl: /DNDEBUG /MD /EHsc /Oy

extern "C" int memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

class Rva00894D90Accessor
{
public:
    static unsigned int decrement(unsigned int *value);
};
__declspec(noinline) void bfmeDropA(void *p);

struct BfmeStringPool3AF0
{
    void *unused;
    void (__cdecl *free)(void *);
};
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;

class Rva008941A0KeyOwner
{
public:
    Rva008941A0KeyOwner(void *key) : m_key(key) { ++*(unsigned short *)m_key; }
    ~Rva008941A0KeyOwner()
    {
        void *old = m_key;
        if (--*(unsigned short *)old == 0)
            g_rva01337A30AllocPair->free(old);
    }
    void *m_key;
};

struct Rva00894120Item
{
    Rva00894120Item(void *key, unsigned state) : first(*(void **)key)
    {
        ++*(unsigned short *)first;
        second = state;
    }
    ~Rva00894120Item()
    {
        void *old = first;
        if (--*(unsigned short *)old == 0)
            g_rva01337A30AllocPair->free(old);
    }
    void *first;
    unsigned second;
};

class BfmeDropObjectA;
class BfmeStrVKI;
class RefHandle008958D0
{
public:
    ~RefHandle008958D0()
    {
        if (m_object)
        {
            if (Rva00894D90Accessor::decrement((unsigned int *)m_object) == 0)
                bfmeDropA(m_object);
        }
    }
    BfmeDropObjectA *m_object;
};

class Rva00893030Manager
{
public:
    void *find008941A0(void *outSlot, void *param);
    RefHandle008958D0 rva00895950(BfmeStrVKI *key);
};
extern Rva00893030Manager *g_rva00893030Manager;

class Rva008941A0Iterator
{
public:
    explicit Rva008941A0Iterator(Rva00894120Item *value) : m_item(value) {}
    __forceinline Rva008941A0Iterator operator+(unsigned count) const { return Rva008941A0Iterator(m_item + count); }
    __forceinline bool operator!=(const Rva008941A0Iterator &other) const { return m_item != other.m_item; }
    __forceinline Rva008941A0Iterator &operator++() { ++m_item; return *this; }
    __forceinline Rva00894120Item *operator->() const { return m_item; }
    Rva00894120Item *m_item;
};

class Rva00894120Vector
{
public:
    void find008941A0(void *param);
    void helper(void *, void *, void *);
    __forceinline void insert(Rva00894120Item *source)
    {
        Rva00894120Item *end2 = &m_items[m_count];
        Rva00894120Item *next2 = source + 1;
        Rva00894120Item *begin2 = source;
        helper(&begin2, &next2, &end2);
    }
private:
    unsigned m_count;
    char m_pad04[4];
    Rva00894120Item *m_items;
};

static __forceinline Rva00894120Item *Rva00894120Next(Rva00894120Item *item)
{
    return item + 1;
}

// ?find008941A0@Rva00894120Vector@@QAEXPAX@Z
void Rva00894120Vector::find008941A0(void *param)
{
    {
        Rva008941A0Iterator item(m_items);
        if (item != Rva008941A0Iterator(m_items) + m_count)
        {
            void *key = *(void **)param;
            int keyLen = *(unsigned short *)((char *)key + 2);
            do
            {
                void *itemKey = item->first;
                int itemLen = *(unsigned short *)((char *)itemKey + 2);
                if (itemLen == keyLen)
                {
                    if (itemKey == key || memcmp((char *)itemKey + 8, (char *)key + 8, itemLen) == 0)
                    {
                        if ((int)item->second == 2)
                            item->second = 3;
                        return;
                    }
                }
                ++item;
            } while (item != Rva008941A0Iterator(m_items) + m_count);
        }
    }
    bool haveNew = g_rva00893030Manager->rva00895950((BfmeStrVKI *)param).m_object != 0;
    Rva00894120Item *end2;
    Rva00894120Item *next2;
    Rva00894120Item *begin2;
    if (haveNew)
    {
        Rva00894120Item newItem(param, 3);
        end2 = &m_items[m_count];
        next2 = &newItem + 1;
        begin2 = &newItem;
        helper(&begin2, &next2, &end2);
    }
    else
    {
        Rva00894120Item newItem(param, 1);
        end2 = &m_items[m_count];
        next2 = &newItem + 1;
        begin2 = &newItem;
        helper(&begin2, &next2, &end2);
    }
}
