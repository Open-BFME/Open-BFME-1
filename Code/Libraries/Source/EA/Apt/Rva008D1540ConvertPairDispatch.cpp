// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008D1540: cdecl dispatch-table body, 350 bytes.
// docs/analysis/0x008985c0.md: both conversions use the same top value.
// The address-derived types describe only the accessed layout.
struct BfmeStringData3AF0 { unsigned short m_refs; };
struct BfmeStringPool3AF0 { void *m_unknown00; void (__cdecl *free)(void *); };
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

class Rva8CD130String
{
public:
    __forceinline Rva8CD130String() {
        m_block = &g_bfmeDefaultString1284;
        ++m_block->m_refs;
    }
    __forceinline ~Rva8CD130String() {
        BfmeStringData3AF0 *old = m_block;
        if (--old->m_refs == 0) g_bfmeStringPool1284->free(old);
    }
    BfmeStringData3AF0 *m_block;
};
class AptValue { public: int toInteger() const; };
class Rva8CD130Value
{
public:
    virtual void addRef();
    virtual void release();
    void getName(Rva8CD130String *);
    unsigned m_flags;
};
class Rva8D0D80Result : public Rva8CD130Value {};
class Rva8D0D80State
{
public:
    Rva8D0D80Result *create(void *, void *, void *, int, int);
    int m_count;
    int m_unknown04;
    Rva8CD130Value **m_stack;
};
struct Rva008D1540Context { void *m_unknown00; void *m_unknown04; void *m_scope08; };
extern Rva8CD130Value *g_bfmeFallbackDB;

void rva008D1540ConvertPairDispatch(Rva8D0D80State *state, Rva008D1540Context *context)
{
    Rva8CD130Value *under = state->m_stack[state->m_count - 2];
    Rva8CD130Value *number = state->m_stack[state->m_count - 3];
    Rva8CD130Value *top = state->m_stack[state->m_count - 1];
    Rva8CD130String first;
    top->getName(&first);
    int count = ((AptValue *)number)->toInteger();
    Rva8CD130String second;
    top->getName(&second);
    Rva8D0D80Result *result = state->create(under, context->m_scope08, &first, count, 1);
    for (int index = 1; index <= 3; ++index) {
        Rva8CD130Value *old = state->m_stack[state->m_count - index];
        if (!((unsigned char)(old->m_flags >> 30) & 1)) old->release();
    }
    state->m_count -= 3;
    if (result) {
        state->m_stack[state->m_count++] = result;
        if (!((unsigned char)(result->m_flags >> 30) & 1)) result->addRef();
        result->release();
    } else {
        Rva8CD130Value *fallback = g_bfmeFallbackDB;
        state->m_stack[state->m_count++] = fallback;
        if (!((unsigned char)(fallback->m_flags >> 30) & 1)) fallback->addRef();
    }
}
