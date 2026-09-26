// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008A9C30: cdecl value/count -> integer-value pointer. Opaque identity.
// Contracts and layouts: docs/analysis/0x008985c0.md, plus retail 008A9C30.
struct BfmeStringData3AF0 {
    unsigned short m_refCount, m_length, m_capacity, m_unknown06;
};
struct BfmeStringPool3AF0 {
    void *m_unknown00;
    void (__cdecl *free)(void *);
};
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
class Rva8CD130String {
public:
    __forceinline Rva8CD130String() {
        m_data = &g_bfmeDefaultString1284;
        ++m_data->m_refCount;
    }
    __forceinline ~Rva8CD130String() {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
    }
    // 0089FF80: ECX is a handle; stack (text pointer, signed start); ret8.
    // +08 reads [ECX], +CD reads text, +F3/+13C return signed EAX.
    int find0089FF80(const char *text, int start);
    BfmeStringData3AF0 *m_data;
};
class Rva8CD130Value { public: void getName(Rva8CD130String *output); };
class AptValue { public: int toInteger() const; };
extern AptValue **g_bfmeArr1233;
extern int g_count01338748;
extern void *(__cdecl *WideAllocPtr)(unsigned int);
struct Rva00899560Value;
struct Rva00899560Pool {
	int m_capacity; int m_count; Rva00899560Value** m_items;
	template<class V> __forceinline void addPooled(V* v)
	{
		int& count = m_count;
		if (count >= m_capacity) {
			v->m_flags &= 0xBFFFFFFF;
			return;
		}
		m_items[count] = v;
		count++;
	}
};
extern Rva00899560Pool* g_rva8CD130IdleHook;
struct Rva00899560Value {
	virtual ~Rva00899560Value();
	unsigned int m_flags;
	__forceinline Rva00899560Value(int type)
	{
		unsigned int flags = (((m_flags & ~0x3f) | type) & 0xF000803F) | 0x8000;
		m_flags = flags;
		if (type != 0x1c && type != 0xa) {
			m_flags = flags | 0x40000000;
			g_rva8CD130IdleHook->addPooled(this);
		} else {
			m_flags = flags & 0xBFFFFFFF;
		}
	}
};
struct Rva008A1110Value : Rva00899560Value {
	int m_value;
	__forceinline void *operator new(unsigned int bytes) { return WideAllocPtr(bytes); }
    __forceinline Rva008A1110Value(int value) : Rva00899560Value(7), m_value(value) {}
};

extern Rva008A1110Value *g_free013387D0;
extern Rva008A1110Value *g_fallback013379BC;
__forceinline Rva008A1110Value *makeInteger008A9C30(int value) {
    Rva008A1110Value *obj = g_free013387D0;
    if (obj) {
        g_free013387D0 = (Rva008A1110Value *)obj->m_value;
        g_rva8CD130IdleHook->addPooled(obj);
        obj->m_value = value;
        return obj;
    }
    return new Rva008A1110Value(value);
}
Rva008A1110Value *findStringValue008A9C30(Rva8CD130Value *value, int count) {
    Rva8CD130String text;
    Rva8CD130String needle;
    int start = 0;
    value->getName(&text);
    if (!count) return g_fallback013379BC;
    Rva8CD130Value *top = (Rva8CD130Value *)g_bfmeArr1233[g_count01338748 - 1];
    top->getName(&needle);
    if (count == 2) {
        start = g_bfmeArr1233[g_count01338748 - 2]->toInteger();
        if (start < 0) start = 0;
    }
    int found = text.find0089FF80((const char *)(needle.m_data + 1), start);
    return makeInteger008A9C30(found);
}
