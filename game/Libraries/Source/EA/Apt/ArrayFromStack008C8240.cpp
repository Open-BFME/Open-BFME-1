// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Second native body in the former 008C8160 scaffold: 008C8240..008C834A.
class AptValue {
public:
    virtual void retain();
    virtual void release();
    unsigned m_valueBits;
    int toInteger() const;
    bool flag30() const { return ((m_valueBits >> 30) & 1) != 0; }
};
class BfmeItemDX;
void bfmePush(BfmeItemDX *);
// ?bfmeRemove@@YAXPAVBfmeItemDX@@@Z  (retail 0x00897330)
void bfmeRemove(BfmeItemDX *);
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned);
extern void (__cdecl *g_Va01337830)(void *, unsigned);
class ArrayValue008B9C60 : public AptValue {
public:
    ArrayValue008B9C60();
    char m_unmodelled08[0x24];
    void *operator new(unsigned n) {
        void *raw = Rva008C5D70Alloc(n + 8);
        char *p = (char *)raw + 8;
        bfmePush((BfmeItemDX *)p);
        return p;
    }
    void operator delete(void *p, unsigned n) {
        bfmeRemove((BfmeItemDX *)p);
        g_Va01337830((char *)p - 8, n + 8);
    }
};
class BfmeE1242;
class BfmeN1242 { public: void rva008B8E10(int, BfmeE1242 *); };
struct Stack008C8240 {
    int m_count, m_capacity;
    AptValue **m_values;
    __forceinline void pop(int n) {
        for (int i=1; i<=n; ++i) {
            AptValue *v = m_values[m_count-i];
            if (!v->flag30()) v->release();
        }
        m_count -= n;
    }
    __forceinline void push(AptValue *v) {
        m_values[m_count++] = v;
        if (!v->flag30()) v->retain();
    }
};
void ArrayFromStack008C8240(Stack008C8240 *state) {
    int count = state->m_values[state->m_count-1]->toInteger();
    state->pop(1);
    ArrayValue008B9C60 *array = new ArrayValue008B9C60;
    array->retain();
    for (int i=0; i<count; ++i)
        ((BfmeN1242 *)array)->rva008B8E10(i, (BfmeE1242 *)state->m_values[state->m_count-i-1]);
    if (count>0) state->pop(count);
    state->push(array);
    array->release();
}
