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

// Retail's pooled-node head is the global at 0x013387D4,
// ?g_rva008D2A80@@3PAVRva008D2A80@@A, defined by Rva008D2A80Link.cpp.
class Rva008D2A80;
extern Rva008D2A80 *g_rva008D2A80;
extern Rva00899560Pool *g_rva01337810GcRoots;
extern void *(*Rva008C5D70Alloc)(unsigned int bytes);
extern "C" const char __identifier("??_7Rva00899560Value@@6B@")[];
// 0x011360A8 is Rva008995E0Value's vftable, emitted as a COMDAT by
// Rva008995E0AptBoolValueCtor.cpp; the stand-in name declared here resolved
// nothing.  __identifier spells the compiler-emitted symbol, and the array
// type keeps the decay-to-pointer that retail's `mov dword ptr [eax], imm32`
// needs (a plain int declaration would load the vftable's first slot instead).
extern "C" const char __identifier("??_7Rva008995E0Value@@6B@")[];

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
    AptBoolean *object = (AptBoolean *)g_rva008D2A80;

    if (object != 0)
    {
        g_rva008D2A80 = (Rva008D2A80 *)object->m_next;
        g_rva01337810GcRoots->addPooled((Rva008D2A30Node *)object);
        object->m_value = value;
        return object;
    }

    object = (AptBoolean *)Rva008C5D70Alloc(12);

    if (object != 0)
    {
        *(void **)object = (void *)__identifier("??_7Rva00899560Value@@6B@");
        object->m_flags = (object->m_flags & 0xf0008005) | 0x40008005;
        g_rva01337810GcRoots->addPooled((Rva008D2A30Node *)object);
        *(void **)object = (void *)__identifier("??_7Rva008995E0Value@@6B@");
        object->m_value = value;
        return object;
    }

    return 0;
}
