// ?d_008c6ad0@@YAXXZ
// partial score=0.833 date=2026-09-26
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Address-qualified callback; AptValue layout matches toNumber/toInteger.
class AptValue {
public:
    float toNumber();
    void *m_vtable;
    unsigned m_valueBits;
    bool m_boolean;
    __forceinline bool isType(int t) const { return (m_valueBits & 63) == t && !isUndefined(); }
    bool isUndefined() const { return ((m_valueBits >> 15) & 1) == 0; }
};
class AptBoolean : public AptValue { public: static AptBoolean *Create(bool); };
extern AptValue *g_bfmeFallbackDB;
extern AptValue **g_bfmeArr1233;
extern int g_bfmeCount1233;
extern const float BfmeZeroRange;
void d_008c4a30();
__forceinline AptValue *coerce(AptValue *v) {
    int t = v->m_valueBits & 63;
    if (t == 5) { bool b = v->m_boolean; return AptBoolean::Create(b); }
    if (t == 6) { if(v->toNumber() != BfmeZeroRange) return AptBoolean::Create(true); return AptBoolean::Create(false); }
    if (t == 7) { if(v->toNumber() != BfmeZeroRange) return AptBoolean::Create(true); return AptBoolean::Create(false); }
    return AptBoolean::Create(false);
}
AptValue *BooleanCoerce008C6AD0(void *, int count) {
    if (!count) return g_bfmeFallbackDB;
    AptValue *v = g_bfmeArr1233[g_bfmeCount1233 - 1];
    int type = v->m_valueBits & 63;
    if (type >= 12 && type <= 19 && !v->isUndefined()) return AptBoolean::Create(true);
    if (type == 27 && !v->isUndefined()) return AptBoolean::Create(true);
    if (v == g_bfmeFallbackDB) return AptBoolean::Create(false);
    if (!v->isType(6) && !v->isType(7)) {
        if (((bool (__cdecl *)(AptValue *))d_008c4a30)(v)) return AptBoolean::Create(false);
        if (v->toNumber() != BfmeZeroRange) return AptBoolean::Create(true);
        return AptBoolean::Create(false);
    }
    return coerce(v);
}
