// ?bfmeSubmitEVA@Rva00893030Manager@@QAEXPAVBfmeStrVKI@@@Z
// partial score=0.961 date=2026-10-09
// cl: /EHsc
// Retail manager submission with two scoped reference handles.

struct BfmeHdrVKI
{
    unsigned short m_refCount;
    unsigned short m_length;
    unsigned short m_capacity;
    unsigned short m_flags;
    char m_data[1];
};

struct BfmeStringPool3AF0
{
    void *m_unused;
    void (__cdecl *free)(void *);
};

extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;
extern void (*TheBfmeFree)(void *, unsigned int);
extern void (__cdecl *g_rva0133784C)(void *);

class BfmeStrVKI
{
public:
    BfmeStrVKI(const char *text) { bfmeSetVKI(text); }
    void __declspec(nothrow) bfmeSetVKI(const char *text);
    ~BfmeStrVKI()
    {
        BfmeHdrVKI *data = m_data;
        if (--data->m_refCount == 0)
            g_rva01337A30AllocPair->free(data);
    }
    BfmeHdrVKI *m_data;
};

struct Rva00895D30Entry
{
    const char *m_name;
    char m_rest[12];
};

struct Rva00895D30Dependencies
{
    char m_pad[0x28];
    int m_count;
    Rva00895D30Entry *m_entries;
};

class BfmeString3AF0
{
public:
    BfmeHdrVKI *m_data;
};

class BfmeDropObjectA
{
public:
    ~BfmeDropObjectA();
    void operator delete(void *p, unsigned int bytes) { TheBfmeFree(p, bytes); }
    unsigned int m_refCount;
    BfmeString3AF0 m_string;
    int m_kind;
    void *m_argument;
    Rva00895D30Dependencies *m_object;
    void *m_buffer;
};

class Rva00894D90Accessor
{
public:
    static unsigned int decrement(unsigned int *value) { return --*value; }
};

class RefHandle008958D0
{
public:
    RefHandle008958D0() { m_object = 0; }
    RefHandle008958D0(BfmeDropObjectA *o) { m_object = o; if (o) ++o->m_refCount; }
    ~RefHandle008958D0()
    {
        BfmeDropObjectA *o = m_object;
        if (o && Rva00894D90Accessor::decrement(&o->m_refCount) == 0)
            delete o;
    }
    BfmeDropObjectA *m_object;
};

class RefHandle008956C0
{
public:
    RefHandle008956C0(const RefHandle008958D0 &other)
    {
        BfmeDropObjectA *o = other.m_object;
        m_object = o;
        if (o)
            ++o->m_refCount;
    }
    ~RefHandle008956C0()
    {
        BfmeDropObjectA *o = m_object;
        if (o && Rva00894D90Accessor::decrement(&o->m_refCount) == 0)
            delete o;
    }
    BfmeDropObjectA *m_object;
};

class Rva008956C0List
{
public:
    int contains008956C0(RefHandle008956C0 candidate);
};
extern Rva008956C0List *g_bfmeTracker4310;

class Rva00893030Manager
{
public:
    __declspec(noinline) RefHandle008958D0 find008958D0(BfmeStrVKI *key);
    void bfmeSubmitEVA(BfmeStrVKI *name);
private:
    class Rva00893030Node *m_head;
};

extern "C" int memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)
class Rva00893030Node
{
public:
    BfmeDropObjectA *m_object;
    Rva00893030Node *m_next;
};

// ?find008958D0@Rva00893030Manager@@QAE?AVRefHandle008958D0@@PAVBfmeStrVKI@@@Z
inline RefHandle008958D0 Rva00893030Manager::find008958D0(BfmeStrVKI *key)
{
    Rva00893030Node *n = m_head;
    if (n)
    {
        BfmeHdrVKI *k = key->m_data;
        int len = k->m_length;
        do
        {
            const BfmeString3AF0 &s = n->m_object->m_string;
            if (len == s.m_data->m_length)
            {
                if (k == s.m_data || memcmp(k->m_data, s.m_data->m_data, len) == 0)
                    return RefHandle008958D0(n->m_object);
            }
            n = n->m_next;
        }
        while (n);
    }
    return RefHandle008958D0();
}

// ?bfmeSubmitEVA@Rva00893030Manager@@QAEXPAVBfmeStrVKI@@@Z
void Rva00893030Manager::bfmeSubmitEVA(BfmeStrVKI *name)
{
    RefHandle008958D0 value = find008958D0(name);
    BfmeDropObjectA *object = value.m_object;
    if (!object)
        return;
    if (object->m_kind == 1)
    {
    }
    else if (object->m_kind == 2)
    {
        if (object->m_buffer)
            g_rva0133784C(object->m_buffer);
    }
    else if (object->m_kind == 3 || object->m_kind == 4 || object->m_kind == 5)
    {
        for (int i = 0; i < object->m_object->m_count; ++i)
        {
            RefHandle008958D0 child = find008958D0(&BfmeStrVKI(object->m_object->m_entries[i].m_name));
            if (child.m_object && !g_bfmeTracker4310->contains008956C0(child))
                bfmeSubmitEVA(&BfmeStrVKI(object->m_object->m_entries[i].m_name));
        }
    }
    if (Rva00894D90Accessor::decrement(&object->m_refCount) == 0)
        delete object;
}
