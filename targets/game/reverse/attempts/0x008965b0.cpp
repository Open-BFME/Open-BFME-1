// ?Rva008965B0@Rva00893030Manager@@QAEXXZ
// partial score=0.4119 date=2026-10-09
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Address-derived manager state loop at retail RVA 0x008965B0.

class Rva008A25C0Object
{
public:
    void rva008A12C0(void *, void *);
};

struct BfmeString3AF0
{
    void *m_data;
};

class BfmeDropObjectA
{
public:
    ~BfmeDropObjectA();
    int m_refCount;
    BfmeString3AF0 m_string;
    int m_kind;
    void *m_argument;
    Rva008A25C0Object *m_object;
    void *m_buffer;
};

extern void (*TheBfmeFree)(void *, unsigned int);
extern void (__cdecl *g_bfmeSlot07VB)(void);

class Rva00893030Ref
{
public:
    Rva00893030Ref(void *value) : m_value(value) {}
    Rva00893030Ref(BfmeDropObjectA *value) : m_value(value)
    {
        if (value)
            ++value->m_refCount;
    }
    Rva00893030Ref(const Rva00893030Ref &other) : m_value(other.m_value)
    {
        if (m_value)
            ++((BfmeDropObjectA *)m_value)->m_refCount;
    }
    ~Rva00893030Ref()
    {
        BfmeDropObjectA *obj = (BfmeDropObjectA *)m_value;
        if (obj && --obj->m_refCount == 0)
        {
            obj->~BfmeDropObjectA();
            TheBfmeFree(obj, sizeof(BfmeDropObjectA));
        }
    }
    void *m_value;
};

struct Rva00893030Node
{
    BfmeDropObjectA *m_object;
    Rva00893030Node *m_next;
};

void __cdecl Rva00896470(Rva00893030Ref value);
typedef void (__cdecl *Rva008965B0Callback)(const char *, Rva00893030Ref);

class Rva00893030Manager
{
public:
    void Rva008965B0();
    bool Rva00895B20(Rva00893030Ref value);
    Rva00893030Node *m_head;
};

// ?Rva008965B0@Rva00893030Manager@@QAEXXZ
void Rva00893030Manager::Rva008965B0()
{
    bool changed;
    do
    {
        changed = false;
        for (Rva00893030Node *node = m_head; node; node = node->m_next)
        {
            Rva00893030Ref value(node->m_object);
            BfmeDropObjectA *obj = (BfmeDropObjectA *)value.m_value;
            bool done = false;
            while (!done)
            {
                switch (obj->m_kind)
                {
                case 1:
                    obj->m_kind = 2;
                    ((Rva008965B0Callback)g_bfmeSlot07VB)((const char *)obj->m_string.m_data + 8, value);
                    break;
                case 2:
                    done = true;
                    break;
                case 3:
                    if (!Rva00895B20(value))
                        done = true;
                    else
                    {
                        obj->m_kind = 4;
                        changed = true;
                        ((Rva008A25C0Object *)((char *)obj->m_object + 8))->rva008A12C0(obj->m_object, obj->m_buffer);
                        Rva00893030Ref temporary(value);
                        Rva00896470(temporary);
                    }
                    break;
                case 4:
                case 5:
                    done = true;
                    break;
                }
            }
        }
    }
    while (changed);
}
