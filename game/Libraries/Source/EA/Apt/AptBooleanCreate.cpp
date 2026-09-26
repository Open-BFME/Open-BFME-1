// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// EA Apt boolean factory. The pooled node and registry offsets come from the
// shared Apt value constructors and the caller set at 0x008C7140-0x008C73B0.

#pragma comment(linker, "/alternatename:?d_008996b0@@YAXXZ=?Create@AptBoolean@@SAPAV1@_N@Z")

struct Rva008D2A30Node
{
    void *m_vtable;
    unsigned int m_flags;
    union
    {
        Rva008D2A30Node *m_next;
        char m_value;
    };
};

struct Rva00899560Pool
{
    int m_capacity;
    int m_count;
    Rva008D2A30Node **m_items;

    __forceinline void addPooled(Rva008D2A30Node *node)
    {
        int &count = m_count;
        if (count >= m_capacity)
        {
            node->m_flags &= 0xbfffffff;
        }
        else
        {
            m_items[count] = node;
            count++;
        }
    }
};

extern Rva008D2A30Node *Rva008D2A30Head;
extern Rva00899560Pool *g_rva8CD130IdleHook;
extern void *(*Rva008C5D70Alloc)(unsigned int bytes);

class AptValue
{
public:
    virtual ~AptValue();
    unsigned int m_flags;
};

class AptBoolean : public AptValue
{
public:
    static AptBoolean *Create(bool value);

    union
    {
        AptBoolean *m_next;
        bool m_value;
    };
};

AptBoolean *AptBoolean::Create(bool value)
{
    AptBoolean *object = (AptBoolean *)Rva008D2A30Head;

    if (object != 0)
    {
        Rva008D2A30Head = (Rva008D2A30Node *)object->m_next;
        g_rva8CD130IdleHook->addPooled((Rva008D2A30Node *)object);
        object->m_value = value;
        return object;
    }

    object = (AptBoolean *)Rva008C5D70Alloc(12);

    if (object != 0)
    {
        *(void **)object = (void *)0x01135D68;
        object->m_flags = (object->m_flags & 0xf0008005) | 0x40008005;
        g_rva8CD130IdleHook->addPooled((Rva008D2A30Node *)object);
        *(void **)object = (void *)0x011360A8;
        object->m_value = value;
        return object;
    }

    return 0;
}
