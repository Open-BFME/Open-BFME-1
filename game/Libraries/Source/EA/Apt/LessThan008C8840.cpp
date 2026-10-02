// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Address-qualified mixed string/integer/float ordering action.
extern "C" int strcmp(const char *, const char *);
#pragma intrinsic(strcmp)
struct StringHandle008C8840 { void *data; __forceinline int compare(const StringHandle008C8840 &other) const { return strcmp((const char *)data+8,(const char *)other.data+8); } };
class AptValue {
public:
    virtual void retain();
    virtual void release();
    union { unsigned m_valueBits; struct { unsigned m_type:6; unsigned m_bits06:9; unsigned m_valid15:1; }; };
    void *m_payload08;
    char m_unmodelled0C[0x14];
    AptValue *m_indirectValue;
    float toNumber();
    int toInteger() const;
    bool isUndefined() const { return ((unsigned char)~(m_valueBits >> 15) & 1) != 0; }
    bool flag30() const { return ((m_valueBits >> 30) & 1) != 0; }
    bool isString() const { return ((m_valueBits & 63)==1 || (m_valueBits & 63)==42) && !isUndefined(); }
    int type() const { return m_valueBits & 63; }
    __forceinline bool isFloat() const { bool undefined=isUndefined(); return m_type==6 && !undefined; }
    __forceinline const StringHandle008C8840 &text() const { return *(const StringHandle008C8840 *)&(((m_valueBits & 63)==1 ? this : m_indirectValue)->m_payload08); }
};
class AptBoolean : public AptValue { public: static AptBoolean *Create(bool); };
unsigned int AptGetSwfVersion();
void d_008c4a30();
extern AptValue *g_bfmeFallbackDB;
struct Stack008C8840 {
    int m_count, m_capacity;
    AptValue **m_values;
    __forceinline void pop(int n) {
        for (int i=1;i<=n;++i) {
            AptValue *v=m_values[m_count-i];
            if (!v->flag30()) v->release();
        }
        m_count-=n;
    }
    __forceinline void push(AptValue *v) {
        m_values[m_count++]=v;
        if (!v->flag30()) v->retain();
    }
};
void LessThan008C8840(Stack008C8840 *state) {
    AptValue *under=state->m_values[state->m_count-2];
    AptValue *top=state->m_values[state->m_count-1];
    if (AptGetSwfVersion()==7 && (top->isUndefined() || under->isUndefined())) {
        state->pop(2); state->push(g_bfmeFallbackDB); return;
    }
    int comparison;
    if (top->isString() && under->isString()) {
        comparison=under->text().compare(top->text())<0;
    } else {
        if (((bool (__cdecl *)(AptValue *))d_008c4a30)(top) || ((bool (__cdecl *)(AptValue *))d_008c4a30)(under)) {
            state->pop(2); state->push(g_bfmeFallbackDB); return;
        }
        if (top->isFloat() || under->isFloat()) {
            float left=under->toNumber();
            float right=top->toNumber();
            comparison=left<right;
        } else {
            int left=under->toInteger();
            int right=top->toInteger();
            comparison=left<right;
        }
    }
    under=AptBoolean::Create(comparison != 0);
    state->pop(2); state->push(under);
}
