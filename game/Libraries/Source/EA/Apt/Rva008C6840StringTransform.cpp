// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008C6840: cdecl callback; no incoming arguments are read.
// Layout witnesses: docs/analysis/0x008985c0.md, sections B/C/E.
// 008C54A0 reads its sole stack argument at +30 and returns with plain ret
// at +104. It mutates the one-pointer handle; its return is unused here.

struct BfmeStringData3AF0
{
    unsigned short m_refCount, m_length, m_capacity, m_unknown06;
};
struct BfmeStringPool3AF0
{
    void *m_unknown00;
    void (__cdecl *free)(void *);
};
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int);

class Rva8CD130String
{
public:
    Rva8CD130String()
    {
        m_data = &g_bfmeDefaultString1284;
        ++m_data->m_refCount;
    }
    ~Rva8CD130String()
    {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0)
            g_rva01337A30AllocPair->free(old);
    }
    Rva8CD130String &rva0089EA60Append(const char *text);
    BfmeStringData3AF0 *m_data;
};
class Rva8CD130Value
{
public:
    void getName(Rva8CD130String *output);
    bool isUndefined() const { return ((m_flags >> 15) & 1) == 0; }
    void *m_unknown00;
    unsigned m_flags;
};
class BfmeStrVKK
{
public:
    void bfmeTruncVKK(unsigned n);
};
class BfmeStrVKJ
{
public:
    BfmeStrVKJ *bfmeAssignVKJ(const BfmeStrVKJ &other);
};
// Existing opaque sized-deallocator pin. Retail EH state 0 pushes 16 and
// the allocation pointer, calls 00891A80, then removes eight argument bytes.
// 00891A80 is the six-byte jump through callback VA 01337830.
class Gen_uws16_00891a80
{
public:
    static void operator delete(void *memory, unsigned bytes);
};
class Rva008A9B00 : public Gen_uws16_00891a80
{
public:
    Rva008A9B00();
    void *operator new(unsigned bytes) { return Rva008C5D70Alloc(bytes); }
    void *m_unknown00;
    unsigned m_flags;
    BfmeStringData3AF0 *m_data;
    Rva008A9B00 *m_next;
};
struct Rva00899560Pool
{
    int m_capacity, m_count;
    void **m_items;
    __forceinline void addPooled(Rva008A9B00 *object)
    {
        int index = m_count;
        int *count = &m_count;
        if (index >= m_capacity)
            object->m_flags &= ~0x40000000;
        else
        {
            m_items[index] = object;
            ++*count;
        }
    }
};
extern Rva00899560Pool *g_rva01337810GcRoots;
// The Apt global node free list at 0x01338478, defined once by
// game/GameEngine/Source/Common/Data/Rva01338478.cpp.  These bodies keep their
// own view of a node (Rva008A9B00) and reach the next link through it.
struct Rva008C3B60Node;
extern Rva008C3B60Node *g_rva01338478NodeHead;
static __forceinline Rva008A9B00 *&rva01338478FreeHead() {
    return *(Rva008A9B00 **)&g_rva01338478NodeHead;
}
extern Rva8CD130Value **g_bfmeArr1233;
struct Rva008AE770Stack { int field00; };
extern Rva008AE770Stack Rva008AE770TheStack;
extern "C" unsigned long strtoul(const char *text, char **end, int base);
namespace Rva008C54A0
{
void method(Rva8CD130String *text);
}

Rva008A9B00 *rva008C6840StringTransform()
{
    Rva008A9B00 *result = rva01338478FreeHead();
    if (result)
    {
        rva01338478FreeHead() = result->m_next;
        g_rva01337810GcRoots->addPooled(result);
        if (result->m_data != &g_bfmeDefaultString1284)
            ((BfmeStrVKK *)&result->m_data)->bfmeTruncVKK(0);
    }
    else
        result = new Rva008A9B00;
    {
        Rva8CD130Value *value = g_bfmeArr1233[Rva008AE770TheStack.field00 - 1];
        unsigned type = value->m_flags & 0x3f;
        if ((type == 1 || type == 42) && !value->isUndefined())
        {
            Rva8CD130String text;
            value->getName(&text);
            Rva008C54A0::method(&text);
            ++text.m_data->m_refCount;
            BfmeStringData3AF0 *old = result->m_data;
            if (--old->m_refCount == 0)
                g_rva01337A30AllocPair->free(old);
            result->m_data = text.m_data;
        }
    }
    return result;
}

namespace Rva008C54A0
{
void method(Rva8CD130String *text)
{
    char decoded[2] = "*";
    Rva8CD130String output;
    unsigned int length = text->m_data->m_length;
    ((BfmeStrVKK *)&output)->bfmeTruncVKK(length);

    const char *source = (const char *)text->m_data + 8;
    char current = *source++;
    while (current)
    {
        if (current == '+')
            decoded[0] = ' ';
        else if (current == '%' && source[0] != 0)
        {
            char secondDigit = source[1];
            char hex[3];
            hex[0] = source[0];
            hex[1] = secondDigit;
            hex[2] = 0;
            decoded[0] = (char)strtoul(hex, 0, 16);
            source += 2;
        }
        else
            decoded[0] = current;

        output.rva0089EA60Append(decoded);
        current = *source++;
    }

    ++output.m_data->m_refCount;
    BfmeStringData3AF0 *old = text->m_data;
    if (--old->m_refCount == 0)
        g_rva01337A30AllocPair->free(old);
    text->m_data = output.m_data;
}
}
