// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008AD530: receiver strings at +18/+1C; scope chain +4C; ret4.
// Layout/callee evidence: docs/analysis/0x008985c0.md and retail instructions.
// Names retain addresses because original proprietary identities are unproved.
struct BfmeStringData3AF0 { unsigned short m_refCount, m_length, m_capacity, m_unknown06; };
struct BfmeStringPool3AF0 { void *m_unknown00; void (__cdecl *free)(void *); };
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int);

class BfmeStrVKI {
public:
    BfmeStrVKI(const char *text) { bfmeSetVKI(text); }
    void bfmeSetVKI(const char *text);
    __forceinline ~BfmeStrVKI() {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
    }
    __forceinline BfmeStrVKI &operator=(const BfmeStrVKI &source) {
        ++source.m_data->m_refCount;
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
        m_data = source.m_data;
        return *this;
    }
    BfmeStringData3AF0 *m_data;
};
class BfmeStrVKK { public: void bfmeTruncVKK(unsigned int length); };
class Rva8CD130String;
class Rva8CD130Value {
public:
    void getName(Rva8CD130String *output);
    __forceinline bool undefined() const { return (~(m_flags >> 15) & 1) != 0; }
    void *m_unknown00;
    unsigned m_flags;
    char m_gap08[0x44];
    Rva8CD130Value *m_unknown4c;
};
class Rva008A9B00 {
public:
    Rva008A9B00();
    static void *operator new(unsigned bytes) { return Rva008C5D70Alloc(bytes); }
    // Retail unwind 00C58540 passes (allocation,16) to 00891A80,
    // the six-byte jump through callback VA 01337830. Caller removes 8.
    __forceinline static void operator delete(void *memory, unsigned bytes) {
        typedef void (__cdecl *SizedDelete)(void *, unsigned);
        (*(SizedDelete *)0x01337830)(memory, bytes);
    }
    void *m_unknown00;
    unsigned m_flags;
    BfmeStrVKI m_string;
    Rva008A9B00 *m_next;
};
struct Rva008C3B60Node;
extern Rva008C3B60Node *Rva008C3B60Head;
struct Rva00899560Pool {
    int m_capacity, m_count;
    void **m_items;
    __forceinline void add(Rva008A9B00 *node) {
        int index = m_count;
        int *count = &m_count;
        if (index >= m_capacity) node->m_flags &= 0xbfffffff;
        else { m_items[index] = node; ++*count; }
    }
};
extern Rva00899560Pool *g_rva8CD130IdleHook;
class Rva00899770;
struct Rva008AE770Stack {
    Rva00899770 *createString(void *value, int unused, BfmeStrVKI *name, int one, int another, int zero);
};
extern Rva008AE770Stack Rva008AE770TheStack;
class Rva008CF3C0String;
class Rva008CF3C0State {
public:
    void append(void *owner, void *scope, Rva008CF3C0String *name, Rva008A9B00 *node, int a, int b, int c);
};
struct Rva008AD530TextSource { char m_gap00[0x34]; const char *m_text34; };
class Rva008AD530StringBinding {
public:
    void resolve(Rva8CD130Value *scope);
    char m_gap00[0x0c];
    Rva008AD530TextSource *m_unknown0c;
    char m_gap10[8];
    BfmeStrVKI m_string18;
    BfmeStrVKI m_string1c;
};

void Rva008AD530StringBinding::resolve(Rva8CD130Value *scope)
{
    BfmeStrVKI &key = m_string1c;
    if (key.m_data == &g_bfmeDefaultString1284) return;
    if (((char *)key.m_data)[8] == '$') {
        m_string18 = key;
        return;
    }
    while (scope) {
        if (((scope->m_flags & 0x3f) == 13 && !scope->undefined()) ||
            ((scope->m_flags & 0x3f) == 18 && !scope->undefined())) break;
        if (!scope->m_unknown4c) break;
        scope = scope->m_unknown4c;
    }
    Rva8CD130Value *value = (Rva8CD130Value *)Rva008AE770TheStack.createString(scope, 0, &key, 1, 1, 0);
    if (value->undefined()) {
        Rva008A9B00 *node = (Rva008A9B00 *)Rva008C3B60Head;
        if (node) {
            Rva008C3B60Head = (Rva008C3B60Node *)node->m_next;
            g_rva8CD130IdleHook->add(node);
            if (node->m_string.m_data != &g_bfmeDefaultString1284)
                ((BfmeStrVKK *)&node->m_string)->bfmeTruncVKK(0);
        } else {
            node = new Rva008A9B00();
        }
        node->m_string = BfmeStrVKI(m_unknown0c->m_text34);
        m_string18 = node->m_string;
        ((Rva008CF3C0State *)&Rva008AE770TheStack)->append(scope, 0, (Rva008CF3C0String *)&key, node, 1, 1, 0);
    } else {
        value->getName((Rva8CD130String *)&m_string18);
    }
}
